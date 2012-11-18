/*
 * Copyright 2012 limetree07. All rights reserved.
 *	
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stdafx.h"
#include "CopyUncPathContextMenu.h"
#include <strsafe.h>
#include <Winnetwk.h>
#include <tchar.h>

#pragma comment(lib, "mpr.lib")

extern HINSTANCE g_hInst;

#define IDM_DISPLAY			0			// The command's identifier offset. 
#define VERB_SAMPLEA		"CopyUncPath"	// The command's ANSI verb string
#define VERB_SAMPLEW		L"CopyUncPath"	// The command's Unicode verb string

CCopyUncPathContextMenu::CCopyUncPathContextMenu(void)
{
	m_hMenuBmp = LoadImage(g_hInst, MAKEINTRESOURCE(IDB_COPYUNC), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	m_hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_COPYUNC), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
}

CCopyUncPathContextMenu::~CCopyUncPathContextMenu(void)
{
	if (m_hMenuBmp)
	{
		DeleteObject(m_hMenuBmp);
		m_hMenuBmp = NULL;
	}
	
	if (m_hIcon)
	{
		DestroyIcon(m_hIcon);
		m_hIcon = NULL;
	}
}

void CCopyUncPathContextMenu::OnCopyFileName(HWND hWnd)
{
	DWORD dwRetVal;

	WCHAR Buffer[1024];
	DWORD dwBufferLength = 1024;

	UNIVERSAL_NAME_INFO * unameinfo;

	unameinfo = (UNIVERSAL_NAME_INFO *) &Buffer;
	dwRetVal = ::WNetGetUniversalName(m_szSelectedFile, UNIVERSAL_NAME_INFO_LEVEL, (LPVOID) unameinfo, &dwBufferLength );

	if (dwRetVal == NO_ERROR)
	{
		SetClipboardString(unameinfo->lpUniversalName, hWnd);
	}
	else if (dwRetVal == ERROR_NOT_CONNECTED)
	{
		SetClipboardString(m_szSelectedFile, hWnd);
	}
}

void CCopyUncPathContextMenu::SetClipboardString(LPWSTR uncPath, HWND hWnd)
{
	DWORD len = wcslen(uncPath);
	HGLOBAL hdst;
	LPWSTR dst;

	hdst = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, (len + 1) * sizeof(WCHAR));
	dst = (LPWSTR)GlobalLock(hdst);
	memcpy(dst, uncPath, len * sizeof(WCHAR));
	dst[len] = 0;
	GlobalUnlock(hdst);

	if (!OpenClipboard(hWnd))
	{
		return;
	}
	EmptyClipboard(); 

	if (this->m_szSelectedFile == NULL)
	{
		CloseClipboard();
		return;
	}

	SetClipboardData(CF_UNICODETEXT, hdst);
	CloseClipboard();
}

#pragma region IShellExtInit

IFACEMETHODIMP CCopyUncPathContextMenu::Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT pDataObj, HKEY hProgID)
{
	if (NULL == pDataObj)
	{
		return E_INVALIDARG;
	}

	HRESULT hr = E_FAIL;

	FORMATETC fe = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stm;

	if (SUCCEEDED(pDataObj->GetData(&fe, &stm)))
	{
		HDROP hDrop = static_cast<HDROP>(GlobalLock(stm.hGlobal));
		if (hDrop != NULL)
		{
			UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
			if (nFiles == 1)
			{
				if (0 != DragQueryFile(hDrop, 0, m_szSelectedFile, 
					ARRAYSIZE(m_szSelectedFile)))
				{
					hr = S_OK;
				}
			}

			GlobalUnlock(stm.hGlobal);
		}

		ReleaseStgMedium(&stm);
	}

	return hr;
}

#pragma endregion

#pragma region IContextMenu

IFACEMETHODIMP CCopyUncPathContextMenu::QueryContextMenu(
	HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	if (CMF_DEFAULTONLY & uFlags)
	{
		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
	}

	MENUITEMINFO mii = { sizeof(mii) };
	mii.fMask = MIIM_BITMAP | MIIM_STRING | MIIM_FTYPE | MIIM_ID | MIIM_STATE;
	mii.wID = idCmdFirst + IDM_DISPLAY;
	mii.fType = MFT_STRING;

	const int maxSize = 100;
	wchar_t hExtLabel[maxSize];
	LoadString(g_hInst, IDS_EXTLABEL, hExtLabel, maxSize);
	mii.dwTypeData = hExtLabel;

	if (OSVersion::Instance().IsVistaOrLater())
	{
		mii.hbmpItem = m_bitmapConverter.IconTo32BitBitmap(m_hIcon);
	}
	else
	{
		mii.hbmpItem = static_cast<HBITMAP>(m_hMenuBmp);
	}
	

	if (!InsertMenuItem(hMenu, indexMenu, TRUE, &mii))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_DISPLAY + 1));
}

IFACEMETHODIMP CCopyUncPathContextMenu::GetCommandString(
	UINT_PTR idCommand, UINT uFlags, LPUINT lpReserved, LPSTR pszName, 
	UINT uMaxNameLen)
{
	HRESULT hr = E_INVALIDARG;

	if (idCommand == IDM_DISPLAY)
	{
		switch (uFlags)
		{
		case GCS_VERBA:
			hr = StringCchCopyNA(pszName, 
				lstrlenA(pszName) / sizeof(pszName[0]), 
				VERB_SAMPLEA, uMaxNameLen);
			break;

		case GCS_VERBW:
			hr = StringCchCopyNW((LPWSTR)pszName, 
				lstrlenW((LPWSTR)pszName) / sizeof(pszName[0]), 
				VERB_SAMPLEW, uMaxNameLen);
			break;

		default:
			hr = S_OK;
		}
	}

	return hr;
}

IFACEMETHODIMP CCopyUncPathContextMenu::InvokeCommand(LPCMINVOKECOMMANDINFO pici)
{
	BOOL fUnicode = FALSE;

	if (pici->cbSize == sizeof(CMINVOKECOMMANDINFOEX))
	{
		if((pici->fMask & CMIC_MASK_UNICODE))
		{
			fUnicode = TRUE;
		}
	}

	if (!fUnicode && HIWORD(pici->lpVerb))
	{
		if (StrCmpIA(pici->lpVerb, VERB_SAMPLEA) == 0)
		{
			OnCopyFileName(pici->hwnd);
		}
		else
		{
			return E_FAIL;
		}
	}
	else if(fUnicode && HIWORD(((CMINVOKECOMMANDINFOEX*)pici)->lpVerbW))
	{
		if (StrCmpIW(((CMINVOKECOMMANDINFOEX*)pici)->lpVerbW, 
			VERB_SAMPLEW) == 0)
		{
			OnCopyFileName(pici->hwnd);
		}
		else
		{
			return E_FAIL;
		}
	}
	else
	{
		if (LOWORD(pici->lpVerb) == IDM_DISPLAY)
		{
			OnCopyFileName(pici->hwnd);
		}
		else
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

#pragma endregion

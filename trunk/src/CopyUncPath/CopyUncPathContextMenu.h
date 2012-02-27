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

#pragma once
#include "resource.h"       // main symbols

#include "CopyUncPath_i.h"
#include "BitmapConverter.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

class ATL_NO_VTABLE CCopyUncPathContextMenu :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCopyUncPathContextMenu, &CLSID_CopyUncPathContextMenu>,
	public IShellExtInit, 
	public IContextMenu
{
public:
	CCopyUncPathContextMenu(void);

DECLARE_REGISTRY_RESOURCEID(IDR_COPYUNCPATHCONTEXTMENU)

DECLARE_NOT_AGGREGATABLE(CCopyUncPathContextMenu)

BEGIN_COM_MAP(CCopyUncPathContextMenu)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	// IShellExtInit
	IFACEMETHODIMP Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT pDataObj, HKEY hKeyProgID);

	// IContextMenu
	IFACEMETHODIMP GetCommandString(UINT_PTR idCommand, UINT uFlags, LPUINT lpReserved, LPSTR pszName, UINT uMaxNameLen);
	IFACEMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO pici);
	IFACEMETHODIMP QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);

protected:
	~CCopyUncPathContextMenu(void);

private:
	void OnCopyFileName(HWND hWnd);
	void SetClipboardString(LPWSTR uncPath, HWND hWnd);

	TCHAR m_szSelectedFile[MAX_PATH];
	BitmapConverter m_bitmapConverter;
	HANDLE m_hMenuBmp;
	HICON m_hIcon;

};

OBJECT_ENTRY_AUTO(__uuidof(CopyUncPathContextMenu), CCopyUncPathContextMenu)

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

#include "StdAfx.h"
#include "OSVersion.h"

OSVersion::OSVersion()
{
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osvi);	
}

OSVersion::~OSVersion(void)
{
}

OSVersion& OSVersion::Instance()
{
	static OSVersion instance;
	return instance;
}

bool OSVersion::IsVistaOrLater()
{
	return (osvi.dwMajorVersion >= 6);
}

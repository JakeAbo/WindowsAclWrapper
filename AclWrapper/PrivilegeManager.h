#pragma once

#include <Windows.h>

class PrivilegeManager
{
public:
	static BOOL EnableSinglePrivilege(LPCTSTR lpszPrivilege);

	static BOOL DisableSinglePrivilege(LPCTSTR lpszPrivilege);

private:
	static BOOL SetPrivilege(
		HANDLE hToken,          // access token handle
		LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
		BOOL bEnablePrivilege   // to enable or disable privilege
	);

	static BOOL EnableOrDisableSinglePrivilege(LPCTSTR lpszPrivilege, BOOL value);
};

#include "PrivilegeManager.h"

#include <iostream>
#include <sstream>

BOOL PrivilegeManager::EnableSinglePrivilege(LPCTSTR lpszPrivilege)
{
	return EnableOrDisableSinglePrivilege(lpszPrivilege, TRUE);
}

BOOL PrivilegeManager::DisableSinglePrivilege(LPCTSTR lpszPrivilege)
{
	return EnableOrDisableSinglePrivilege(lpszPrivilege, FALSE);
}

BOOL PrivilegeManager::SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if (!LookupPrivilegeValue(
		NULL,            // lookup privilege on local system
		lpszPrivilege,   // privilege to lookup 
		&luid))        // receives LUID of privilege
	{
		std::cout << "LookupPrivilegeValue error: " << std::system_category().message(GetLastError()) << std::endl;
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	// Enable the privilege or disable all privileges.

	if (!AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		(PTOKEN_PRIVILEGES)NULL,
		(PDWORD)NULL))
	{
		std::cout << "AdjustTokenPrivileges error: " << std::system_category().message(GetLastError()) << std::endl;
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)

	{
		std::cout << "The token does not have the specified privilege." << std::endl;
		return FALSE;
	}

	return TRUE;
}

BOOL PrivilegeManager::EnableOrDisableSinglePrivilege(LPCTSTR lpszPrivilege, BOOL value)
{
	HANDLE hToken = nullptr;

	if (!OpenProcessToken(GetCurrentProcess(),
	                      TOKEN_ADJUST_PRIVILEGES,
	                      &hToken))
	{
		std::cout << "OpenProcessToken error: " << std::system_category().message(GetLastError()) << std::endl;
		if (hToken)
		{
			CloseHandle(hToken);
		}
		return false;
	}

	// Enable the SE_TAKE_OWNERSHIP_NAME privilege.
	if (!SetPrivilege(hToken, lpszPrivilege, value))
	{
		std::cout << "SetPrivilege error: " << std::system_category().message(GetLastError()) << std::endl;
		if (hToken)
		{
			CloseHandle(hToken);
		}
		return false;
	}

	CloseHandle(hToken);
	return true;
}

#include "ProtectedDirectory.h"

#include <iostream>
#include <Sddl.h>

#include "SecurityDescriptor.h"

ProtectedDirectory::ProtectedDirectory(std::wstring path): m_path(std::move(path))
{
	m_handle = CreateFileW(
		m_path.c_str(),
		GENERIC_ALL,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		nullptr);

	if (m_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "CreateFileW error: " << std::system_category().message(GetLastError()) << std::endl;
		return;
	}
}

ProtectedDirectory::~ProtectedDirectory()
{
	if (m_handle)
	{
		CloseHandle(m_handle);
	}
}

bool ProtectedDirectory::ChangeDirectoryDacl(const Dacl& dacl) const
{
	SecurityDescriptor sa;
	sa.InitWithSddlString(dacl.GenerateStringValue());

	const PACL acl = sa.GetDacl();
	if (!acl)
	{
		return false;
	}

	const auto retCode = SetSecurityInfo(
		m_handle,
		SE_FILE_OBJECT,
		DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION,
		nullptr,
		nullptr,
		acl,
		nullptr);

	if (retCode != ERROR_SUCCESS)
	{
		std::cout << "SetSecurityInfo error: " << std::system_category().message(GetLastError()) << std::endl;
		return false;
	}
	
	return true;
}

bool ProtectedDirectory::ChangeDirectoryOwner(const Owner& owner) const
{	
	SecurityDescriptor sa;
	if (sa.InitWithSddlString(owner.GenerateStringValue()))
	{
		return false;
	}

	const PSID pOwner = sa.GetOwner();
	if (!pOwner)
	{
		return false;
	}
	
	const auto retCode = SetSecurityInfo(
		m_handle,
		SE_FILE_OBJECT,
		OWNER_SECURITY_INFORMATION,
		pOwner,
		nullptr,
		nullptr,
		nullptr);

	if (retCode != ERROR_SUCCESS)
	{
		std::cout << "SetSecurityInfo error: " << std::system_category().message(GetLastError()) << std::endl;
		return false;
	}
	
	return true;
}

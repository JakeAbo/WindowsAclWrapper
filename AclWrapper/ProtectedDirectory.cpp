#include "ProtectedDirectory.h"

#include <iostream>
#include <Sddl.h>

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
	PACL acl = nullptr;
	SECURITY_ATTRIBUTES sa;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;

	auto success = ConvertStringSecurityDescriptorToSecurityDescriptor(
		dacl.GenerateStringValue().c_str(),
		SDDL_REVISION_1,
		&sa.lpSecurityDescriptor,
		nullptr);

	if (!success)
	{
		std::cout << "ConvertStringSecurityDescriptorToSecurityDescriptor error: " << std::system_category().message(GetLastError()) << std::endl;
		return false;
	}

	BOOL IsDaclExists;
	BOOL IsDaclDefaultedMechanism;

	success = GetSecurityDescriptorDacl(
		sa.lpSecurityDescriptor,
		&IsDaclExists,
		&acl,
		&IsDaclDefaultedMechanism);

	if (!success)
	{
		std::cout << "GetSecurityDescriptorDacl error: " << std::system_category().message(GetLastError()) << std::endl;
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

	// Free the memory allocated for the SECURITY_DESCRIPTOR.
	if (LocalFree(sa.lpSecurityDescriptor) != NULL)
	{
		std::cout << "LocalFree error: " << std::system_category().message(GetLastError()) << std::endl;
	}

	return true;
}

bool ProtectedDirectory::ChangeDirectoryOwner(const Owner& owner) const
{
	SECURITY_ATTRIBUTES sa;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;

	auto success = ConvertStringSecurityDescriptorToSecurityDescriptor(
		owner.GenerateStringValue().c_str(),
		SDDL_REVISION_1,
		&sa.lpSecurityDescriptor,
		nullptr);

	if (!success)
	{
		std::cout << "ConvertStringSecurityDescriptorToSecurityDescriptor error: " << std::system_category().message(GetLastError()) << std::endl;
		return false;
	}

	PSID pOwner = nullptr;
	BOOL IsOwnerDefaultedMechanism;

	success = GetSecurityDescriptorOwner(
		sa.lpSecurityDescriptor,
		&pOwner,
		&IsOwnerDefaultedMechanism);

	if (!success)
	{
		std::cout << "GetSecurityDescriptorOwner error: " << std::system_category().message(GetLastError()) << std::endl;
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

	// Free the memory allocated for the SECURITY_DESCRIPTOR.
	if (LocalFree(sa.lpSecurityDescriptor) != NULL)
	{
		std::cout << "LocalFree error: " << std::system_category().message(GetLastError()) << std::endl;
	}

	return true;
}

#include "SecurityDescriptor.h"

#include <Sddl.h>

SecurityDescriptor::~SecurityDescriptor()
{
	if (m_sa.lpSecurityDescriptor)
	{
		// Free the memory allocated for the SECURITY_DESCRIPTOR.
		if (LocalFree(m_sa.lpSecurityDescriptor) != nullptr)
		{
			std::cout << "LocalFree error: " << std::system_category().message(GetLastError()) << std::endl;
		}
	}
}

bool SecurityDescriptor::InitWithSddlString(const std::wstring& value)
{
	const auto success = ConvertStringSecurityDescriptorToSecurityDescriptor(
		value.c_str(),
		SDDL_REVISION_1,
		&m_sa.lpSecurityDescriptor,
		nullptr);

	if (!success)
	{
		std::cout << "ConvertStringSecurityDescriptorToSecurityDescriptor error: " << std::system_category().message(GetLastError()) << std::endl;
		return false;
	}

	return true;
}

PACL SecurityDescriptor::GetDacl() const
{
	PACL acl = nullptr;
	BOOL isDaclExists;
	BOOL isDaclDefaultedMechanism;

	if (!m_sa.lpSecurityDescriptor)
	{
		std::cout << "Null SecurityDescriptor" << std::endl;
		return nullptr;
	}

	if(!GetSecurityDescriptorDacl(
		m_sa.lpSecurityDescriptor,
		&isDaclExists,
		&acl,
		&isDaclDefaultedMechanism))
	{
		std::cout << "GetSecurityDescriptorDacl error: " << std::system_category().message(GetLastError()) << std::endl;
		return nullptr;
	}

	return acl;
}

PSID SecurityDescriptor::GetOwner() const
{
	PSID pOwner = nullptr;
	BOOL IsOwnerDefaultedMechanism;

	if (!m_sa.lpSecurityDescriptor)
	{
		std::cout << "Null SecurityDescriptor" << std::endl;
		return nullptr;
	}

	if (!GetSecurityDescriptorOwner(
		m_sa.lpSecurityDescriptor,
		&pOwner,
		&IsOwnerDefaultedMechanism))
	{
		std::cout << "GetSecurityDescriptorOwner error: " << std::system_category().message(GetLastError()) << std::endl;
		return nullptr;
	}

	return pOwner;
}

#pragma once
#include "ProtectedDirectory.h"

class SecurityDescriptor final
{
public:
	SecurityDescriptor() = default;
	~SecurityDescriptor();

	bool InitWithSddlString(const std::wstring& value);
	[[nodiscard]] PACL GetDacl() const;
	[[nodiscard]] PSID GetOwner() const;

private:
	SECURITY_ATTRIBUTES m_sa{ sizeof(SECURITY_ATTRIBUTES), nullptr, false};
};


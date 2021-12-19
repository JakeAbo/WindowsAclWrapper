#pragma once

#include <AclAPI.h>

// https://docs.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-createwellknownsid

class SidWrapper final
{
public:
	SidWrapper() = default;
	SidWrapper(_In_ WELL_KNOWN_SID_TYPE SidType);
	SidWrapper(_In_ const SidWrapper& other);
	SidWrapper& operator=(_In_ const SidWrapper& other);
	SidWrapper(SidWrapper&& other) noexcept = delete;
	SidWrapper& operator=(SidWrapper&& other) noexcept = delete;
	~SidWrapper();

	PSID GetSid() const;

private:
	void Reset(_In_ PSID sid, _In_ DWORD cbSid);
	void Release();

	PSID m_pSid{ nullptr };
	DWORD m_cbSid{ 0 };
};

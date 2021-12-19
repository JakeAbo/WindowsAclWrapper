#include "SidWrapper.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <sstream>
#include <Windows.h>

SidWrapper::SidWrapper(_In_ WELL_KNOWN_SID_TYPE SidType)
{
	// Get size of Sid
	CreateWellKnownSid(
		SidType,
		nullptr,
		nullptr,
		&m_cbSid);

	// Allocate sid
	m_pSid = new byte[m_cbSid];

	// Get sid itself
	const auto success = CreateWellKnownSid(
		SidType,
		nullptr,
		m_pSid,
		&m_cbSid);

	if (!success)
	{
		std::cout << "CreateWellKnownSid error: " << std::system_category().message(GetLastError()) << std::endl;
	}
}

SidWrapper::SidWrapper(_In_ const SidWrapper& other)
{
	Reset(other.m_pSid, other.m_cbSid);
}

SidWrapper& SidWrapper::operator=(_In_ const SidWrapper& other)
{
	if (this != &other)
	{
		Reset(other.m_pSid, other.m_cbSid);
	}
	return *this;
}

SidWrapper::~SidWrapper()
{
	Release();
}

PSID SidWrapper::GetSid() const
{
	return m_pSid;
}

void SidWrapper::Reset(_In_ PSID sid, _In_ DWORD cbSid)
{
	if (!IsValidSid(sid))
	{
		std::cout << "other is not valid sid" << std::endl;
		return;
	}

	if (!EqualSid(sid, m_pSid))
	{
		Release();
		
		m_pSid = new byte[cbSid];
		memcpy(m_pSid, sid, cbSid);
	}
}

void SidWrapper::Release()
{
	if (m_pSid)
	{
		delete[] static_cast<byte*>(m_pSid);
		m_pSid = nullptr;
	}
}

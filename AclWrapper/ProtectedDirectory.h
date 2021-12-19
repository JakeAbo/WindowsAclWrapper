#pragma once

#include "SidWrapper.h"

#include <string>

#include "Dacl.h"

class ProtectedDirectory final
{
public:
	explicit ProtectedDirectory(_In_ std::wstring path);

	~ProtectedDirectory();

	ProtectedDirectory(_In_ const ProtectedDirectory& other) = delete;
	ProtectedDirectory& operator=(_In_ const ProtectedDirectory& other) = delete;
	ProtectedDirectory(_In_ ProtectedDirectory&& other) noexcept = delete;
	ProtectedDirectory& operator=(_In_ ProtectedDirectory&& other) noexcept = delete;

	bool ChangeDirectoryOwnerDeprecated(_In_ const SidWrapper& sid) const;

	bool ChangeDirectoryDacl(_In_ const Dacl& dacl) const;
	bool ChangeDirectoryOwner(_In_ const Owner& owner) const;

	HANDLE GetHandle() const
	{
		return m_handle;
	}

private:
	HANDLE m_handle{ nullptr };
	std::wstring m_path;
};

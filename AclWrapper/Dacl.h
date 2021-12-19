#pragma once

#include "AceEntry.h"
#include <vector>

class Dacl
{
public:
	Dacl() = default;

	Dacl& AddAceEntry(const AceEntry& entry);

	std::wstring GenerateStringValue() const;

private:
	std::vector<AceEntry> m_aceEntries{};
};

class Owner
{
public:
	Owner(Trustee trustee);

	std::wstring GenerateStringValue() const;

private:
	Trustee m_trustee{};
};


#pragma once

#include "AceEntry.h"
#include <vector>

class Dacl final : public SddlItem
{
public:
	Dacl() = default;

	Dacl& AddAceEntry(const AceEntry& entry);

	std::wstring GenerateStringValue() const override;

private:
	std::vector<AceEntry> m_aceEntries{};
};

class Owner final : public SddlItem
{
public:
	Owner(Trustee trustee);

	std::wstring GenerateStringValue() const override;

private:
	Trustee m_trustee{};
};


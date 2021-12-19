#include "Dacl.h"

Dacl& Dacl::AddAceEntry(const AceEntry& entry)
{
	m_aceEntries.push_back(entry);
	return *this;
}

std::wstring Dacl::GenerateStringValue() const
{
	std::wstring result = SddlBuilder().SddlObject(SddlObject::DaclEntries).Colon().GetStringValue();

	for(const auto& entry : m_aceEntries)
	{
		result += entry.GenerateStringValue();
	}

	return result;
}
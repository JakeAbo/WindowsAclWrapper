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
		result += entry.GenerateEntryString();
	}

	return result;
}

Owner::Owner(Trustee trustee)
	: m_trustee(trustee)
{

}

std::wstring Owner::GenerateStringValue() const
{
	return SddlBuilder().SddlObject(SddlObject::Owner).Colon().Trustee(m_trustee).GetStringValue();
}

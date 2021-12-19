#include "Owner.h"
#include "SddlBuilder.h"

Owner::Owner(Trustee trustee)
	: m_trustee(trustee)
{

}

std::wstring Owner::GenerateStringValue() const
{
	return SddlBuilder().SddlObject(SddlObject::Owner).Colon().Trustee(m_trustee).GetStringValue();
}

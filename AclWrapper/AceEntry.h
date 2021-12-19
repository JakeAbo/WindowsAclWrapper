#pragma once

#include "SddlItem.h"
#include "SddlBuilder.h"

class AceEntry : public SddlItem
{
public:
	AceEntry(AceType type = AceType::None, 
		AceFlag flag = AceFlag::None,
		Permissions perm = Permissions::None,
		Trustee trustee = Trustee::None);

	std::wstring GenerateStringValue() const override;

private:
	AceType m_type{ AceType::None };
	AceFlag m_aceFlag{ AceFlag::None };
	Permissions m_permissions{ Permissions::None };
	Trustee m_trustee{ Trustee::None };
};
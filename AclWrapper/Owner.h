#pragma once

#include "BasicTypes.h"
#include "SddlItem.h"

class Owner final : public SddlItem
{
public:
	Owner(Trustee trustee);

	std::wstring GenerateStringValue() const override;

private:
	Trustee m_trustee{};
};

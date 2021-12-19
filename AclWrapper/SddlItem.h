#pragma once
#include <string>

class SddlItem
{
public:
	SddlItem() = default;
	virtual ~SddlItem();

	virtual std::wstring GenerateStringValue() const = 0;
};


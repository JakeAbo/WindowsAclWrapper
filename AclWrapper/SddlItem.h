#pragma once
#include <string>

class SddlItem
{
public:
	SddlItem() = default;
	virtual ~SddlItem() = default;

	virtual std::wstring GenerateStringValue() const = 0;
};


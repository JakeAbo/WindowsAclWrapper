#include "SddlBuilder.h"

SddlBuilder& SddlBuilder::Colon()
{
	m_value += L":";
	return *this;
}

SddlBuilder& SddlBuilder::Semicolon(int times)
{
	for (auto i = 0; i < times; ++i)
	{
		m_value += L";";
	}

	return *this;
}

SddlBuilder& SddlBuilder::LeftBracket()
{
	m_value += L"(";
	return *this;
}

SddlBuilder& SddlBuilder::RightBracket()
{
	m_value += L")";
	return *this;
}

SddlBuilder& SddlBuilder::SddlObject(::SddlObject object)
{
	m_value += GenericField(object);
	return *this;
}

SddlBuilder& SddlBuilder::AceType(::AceType type)
{
	m_value += GenericField(type);
	return *this;
}

SddlBuilder& SddlBuilder::AceFlag(::AceFlag flag)
{
	m_value += GenericField(flag);
	return *this;
}

SddlBuilder& SddlBuilder::Permissions(::Permissions perm)
{
	// We add more 2 semicolons because we don't support Object Type and Inherited Object Type
	m_value += GenericField(perm);
	return *this;
}

SddlBuilder& SddlBuilder::Trustee(::Trustee trustee)
{
	m_value += GenericField(trustee);
	return *this;
}

const std::wstring& SddlBuilder::GetStringValue()
{
	return m_value;
}

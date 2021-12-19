#pragma once

#include "AceTranslator.h"

class SddlBuilder final
{
public:
	SddlBuilder() = default;

	SddlBuilder& Colon();
	SddlBuilder& Semicolon(int times = 1);
	SddlBuilder& LeftBracket();
	SddlBuilder& RightBracket();

	SddlBuilder& SddlObject(SddlObject object);
	SddlBuilder& AceType(AceType type);
	SddlBuilder& AceFlag(AceFlag flag);
	SddlBuilder& Permissions(Permissions perm);
	SddlBuilder& Trustee(Trustee trustee);
	const std::wstring& GetStringValue();

private:
	template<typename T>
	static std::wstring GenericField(T field)
	{
		std::wstring result{};

		try
		{
			result = AceTranslator::TranslateAceField(field);
		}
		catch (const std::out_of_range& ex)
		{
			std::cout << "GenericField exception: " << ex.what() << std::endl;
		}

		return result;
	}

	std::wstring m_value{};
};

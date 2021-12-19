#pragma once

#include <type_traits>
#include <unordered_map>

#include "BasicTypes.h"

class AceTranslator final
{
public:
	template<typename T, std::enable_if_t<is_any<T, SddlObject, AceType, AceFlag, Permissions, Trustee>::value>* = nullptr>
	static std::wstring TranslateAceField(T field) noexcept(false) // throw std::out_of_range
	{
		if constexpr (std::is_same_v<T, SddlObject>)
		{
			return TranslateHelper(field, m_sddlObjects);
		}

		if constexpr (std::is_same_v<T, AceType>)
		{
			return TranslateHelper(field, m_aceTypes);
		}

		else if constexpr (std::is_same_v<T, AceFlag>)
		{
			return TranslateHelper(field, m_aceFlags);
		}

		else if constexpr (std::is_same_v<T, Permissions>)
		{
			return TranslateHelper(field, m_permissions);
		}

		else if constexpr (std::is_same_v<T, Trustee>)
		{
			return TranslateHelper(field, m_trustee);
		}

		return {};
	}

private:
	template<typename T>
	static std::wstring TranslateHelper(T field, const std::unordered_map<T, std::wstring> translatorMap) noexcept(false) // throw std::out_of_range
	{
		std::wstring result{};

		for (size_t i = 0; i < static_cast<std::underlying_type_t<T>>(T::Length); i++)
		{
			if ((static_cast<T>(BIT(i)) & field) != T::None)
			{
				result += translatorMap.at(static_cast<T>(BIT(i)));
			}
		}

		return result;
	}

	static const std::unordered_map<SddlObject, std::wstring> m_sddlObjects;
	static const std::unordered_map<AceType, std::wstring> m_aceTypes;
	static const std::unordered_map<AceFlag, std::wstring> m_aceFlags;
	static const std::unordered_map<Permissions, std::wstring> m_permissions;
	static const std::unordered_map<Trustee, std::wstring> m_trustee;
};

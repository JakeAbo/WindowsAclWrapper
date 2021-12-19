#include "AceEntry.h"

AceEntry::AceEntry(AceType type, AceFlag flag, Permissions perm, Trustee trustee)
	: SddlItem(), m_type(type), m_aceFlag(flag), m_permissions(perm), m_trustee(trustee)
{
		
}

std::wstring AceEntry::GenerateStringValue() const
{
	return SddlBuilder().
	       LeftBracket().
	       AceType(m_type).
	       Semicolon().
	       AceFlag(m_aceFlag).
           Semicolon().
           Permissions(m_permissions).
	       Semicolon(3).
	       Trustee(m_trustee).
	       RightBracket().GetStringValue();
}

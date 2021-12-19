#include "AceTranslator.h"

const std::unordered_map<AceType, std::wstring> AceTranslator::m_aceTypes{
		{AceType::AccessAllowed, L"A"},
		{AceType::AccessDenied, L"D"}
};

const std::unordered_map<SddlObject, std::wstring> AceTranslator::m_sddlObjects{
		{SddlObject::Owner, L"O"},
		{SddlObject::DaclEntries, L"D"}
};

const std::unordered_map<AceFlag, std::wstring> AceTranslator::m_aceFlags{
		{AceFlag::ContainerInherit, L"CI"},
		{AceFlag::ObjectInherit, L"OI"},
		{AceFlag::NoPropagate, L"NP"},
		{AceFlag::InheritanceOnly, L"IO"},
		{AceFlag::AceInherited, L"ID"},
};
const std::unordered_map<Permissions, std::wstring> AceTranslator::m_permissions{
		{Permissions::GenericAll, L"GA"},
		{Permissions::GenericRead, L"GR"},
		{Permissions::GenericWrite, L"GW"},
		{Permissions::GenericExecute, L"GX"},
};
const std::unordered_map<Trustee, std::wstring> AceTranslator::m_trustee{
		{Trustee::AccountOperators, L"AO"},
		{Trustee::AnonymousLogon, L"AN"},
		{Trustee::AuthenticatedUsers, L"AU"},
		{Trustee::BuiltinAdministrators, L"BA"},
		{Trustee::BuiltinGuests, L"BG"},
		{Trustee::BackupOperators, L"BO"},
		{Trustee::BuiltinUsers, L"BU"},
		{Trustee::CertificateServerAdministrators, L"CA"},
		{Trustee::CreatorGroup, L"CG"},
		{Trustee::CreatorOwner, L"CO"},
		{Trustee::DomainAdministrators, L"DA"},
		{Trustee::DomainComputers, L"DC"},
		{Trustee::DomainControllers, L"DD"},
		{Trustee::DomainGuests, L"DG"},
		{Trustee::DomainUsers, L"DU"},
		{Trustee::EnterpriseAdministrators, L"EA"},
		{Trustee::EnterpriseDomainControllers, L"ED"},
		{Trustee::Everyone, L"WD"},
		{Trustee::GroupPolicyAdministrators, L"PA"},
		{Trustee::InteractivelyLoggedOnUser, L"IU"},
		{Trustee::LocalAdministrator, L"LA"},
		{Trustee::LocalGuest, L"LG"},
		{Trustee::LocalServiceAccount, L"LS"},
		{Trustee::LocalSystem, L"SY"},
		{Trustee::NetworkLogonUser, L"NU"},
		{Trustee::NetworkConfigurationOperators, L"NO"},
		{Trustee::NetworkServiceAccount, L"NS"},
		{Trustee::PrinterOperators, L"PO"},
		{Trustee::PersonalSelf, L"PS"},
		{Trustee::PowerUsers, L"PU"},
		{Trustee::RASServersGroup, L"RS"},
		{Trustee::TerminalServerUsers, L"RD"}
};

#pragma once

#include <iostream>

#define BIT(X) 1<<(X)

template<typename E>
E operator |(E a, E b)
{
	static_assert(std::is_enum_v<E>, "type is not enum");
	return static_cast<E>(static_cast<std::underlying_type_t<E>>(a) |
		static_cast<std::underlying_type_t<E>>(b));
}

template<typename E>
E& operator |=(E& a, E b)
{
	return a = a | b;
}

template<typename E>
E operator &(E a, E b)
{
	static_assert(std::is_enum_v<E>, "type is not enum");
	return static_cast<E>(static_cast<std::underlying_type_t<E>>(a) &
		static_cast<std::underlying_type_t<E>>(b));
}

template<typename E>
E& operator &=(E& a, E b)
{
	return a = a & b;
}

template<typename E>
E operator ~(E a)
{
	static_assert(std::is_enum_v<E>, "type is not enum");
	return static_cast<E>(~static_cast<std::underlying_type_t<E>>(a));
}

template <class T, class... Ts>
struct is_any : std::disjunction<std::is_same<T, Ts>...> {};

enum class SddlObject : uint32_t
{
	None = 0,

	Owner		= BIT(0),
	DaclEntries = BIT(1),

	Length = 2,
};

enum class AceType : uint32_t
{
	None = 0,

	AccessAllowed = BIT(0),
	AccessDenied = BIT(1),

	Length = 2,
};

enum class AceFlag : uint32_t
{
	None = 0,

	ContainerInherit = BIT(0),
	ObjectInherit = BIT(1),
	NoPropagate = BIT(2),
	InheritanceOnly = BIT(3),
	AceInherited = BIT(4),

	Length = 5,
};

enum class Permissions : uint32_t
{
	None = 0,

	GenericAll = BIT(0),
	GenericRead = BIT(1),
	GenericWrite = BIT(2),
	GenericExecute = BIT(3),

	Length = 4,
};

enum class Trustee : uint64_t
{
	None = 0,

	AccountOperators = BIT(0),
	AnonymousLogon = BIT(1),
	AuthenticatedUsers = BIT(2),
	BuiltinAdministrators = BIT(3),
	BuiltinGuests = BIT(4),
	BackupOperators = BIT(5),
	BuiltinUsers = BIT(6),
	CertificateServerAdministrators = BIT(7),
	CreatorGroup = BIT(8),
	CreatorOwner = BIT(9),
	DomainAdministrators = BIT(10),
	DomainComputers = BIT(11),
	DomainControllers = BIT(12),
	DomainGuests = BIT(13),
	DomainUsers = BIT(14),
	EnterpriseAdministrators = BIT(15),
	EnterpriseDomainControllers = BIT(16),
	Everyone = BIT(17),
	GroupPolicyAdministrators = BIT(18),
	InteractivelyLoggedOnUser = BIT(19),
	LocalAdministrator = BIT(20),
	LocalGuest = BIT(21),
	LocalServiceAccount = BIT(22),
	LocalSystem = BIT(23),
	NetworkLogonUser = BIT(24),
	NetworkConfigurationOperators = BIT(25),
	NetworkServiceAccount = BIT(26),
	PrinterOperators = BIT(27),
	PersonalSelf = BIT(28),
	PowerUsers = BIT(29),
	RASServersGroup = BIT(30),
	TerminalServerUsers = BIT(31),

	Length = 32,
};
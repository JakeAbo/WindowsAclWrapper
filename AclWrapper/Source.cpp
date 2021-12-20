#include <iostream>
#include <string>
#include "AclAPI.h"
#include <Windows.h>

#include "ProtectedDirectory.h"

#include "Sddl.h"

#include <unordered_map>
#include "SddlBuilder.h"
#include "Dacl.h"
#include "Owner.h"

int main()
{
	ProtectedDirectory myDir{ L"C:\\ProgramData\\0006" };
	if (myDir.ChangeDirectoryOwner(Owner(Trustee::BuiltinAdministrators)/*WinBuiltinAdministratorsSid*//*WinLocalSystemSid*/))
	{
		std::cout << "success to change to system owner" << std::endl;
	}

	const auto dacl = Dacl()
		.AddAceEntry(
			AceEntry(
				AceType::AccessDenied,
				AceFlag::ObjectInherit | AceFlag::ContainerInherit,
				Permissions::GenericAll,
				Trustee::BuiltinGuests))
		.AddAceEntry(
			AceEntry(
				AceType::AccessDenied,
				AceFlag::ObjectInherit | AceFlag::ContainerInherit,
				Permissions::GenericAll,
				Trustee::AnonymousLogon))
		.AddAceEntry(
			AceEntry(
				AceType::AccessAllowed,
				AceFlag::ObjectInherit | AceFlag::ContainerInherit,
				Permissions::GenericAll,
				Trustee::LocalSystem))
		.AddAceEntry(
			AceEntry(
				AceType::AccessAllowed,
				AceFlag::ObjectInherit | AceFlag::ContainerInherit,
				Permissions::GenericAll,
				Trustee::BuiltinAdministrators));

	if (myDir.ChangeDirectoryDacl(dacl))
	{
		std::cout << "success to change dacl" << std::endl;
	}
	
	return 0;
}

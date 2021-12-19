#include <iostream>
#include <string>
#include "AclAPI.h"
#include <Windows.h>

#include "ProtectedDirectory.h"

#include "Sddl.h"

#include <unordered_map>
#include "SddlBuilder.h"
#include "Dacl.h"

// CreateMyDACL.
//    Create a security descriptor that contains the DACL 
//    you want.
//    This function uses SDDL to make Deny and Allow ACEs.
//
// Parameter:
//    SECURITY_ATTRIBUTES * pSA
//    Pointer to a SECURITY_ATTRIBUTES structure. It is your
//    responsibility to properly initialize the 
//    structure and to free the structure's 
//    lpSecurityDescriptor member when you have
//    finished using it. To free the structure's 
//    lpSecurityDescriptor member, call the 
//    LocalFree function.
// 
// Return value:
//    FALSE if the address to the structure is NULL. 
//    Otherwise, this function returns the value from the
//    ConvertStringSecurityDescriptorToSecurityDescriptor 
//    function.
BOOL CreateMyDACL(SECURITY_ATTRIBUTES* pSA)
{
	// Define the SDDL for the DACL. This example sets 
	// the following access:
	//     Built-in guests are denied all access.
	//     Anonymous logon is denied all access.
	//     Authenticated users are allowed 
	//     read/write/execute access.
	//     Administrators are allowed full control.
	// Modify these values as needed to generate the proper
	// DACL for your application. 
	//const auto szSD = TEXT("D:")       // Discretionary ACL
	//	TEXT("(D;OICI;GA;;;BG)")     // Deny access to 
	//								 // built-in guests
	//	TEXT("(D;OICI;GA;;;AN)")     // Deny access to 
	//								 // anonymous logon
	//	TEXT("(A;OICI;GA;;;SY)")     // Allow 
	//								 // read/write/execute 
	//								 // to authenticated 
	//								 // users
	//	TEXT("(A;OICI;GA;;;BA)");    // Allow full control 
	//								 // to administrators


	const auto szSD = Dacl()
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
				Trustee::BuiltinAdministrators))
		.GenerateStringValue();
		

	if (NULL == pSA)
		return FALSE;

	return ConvertStringSecurityDescriptorToSecurityDescriptor(
		szSD.c_str(),
		SDDL_REVISION_1,
		&(pSA->lpSecurityDescriptor),
		NULL);
}

int main()
{
	ProtectedDirectory myDir{ L"C:\\ProgramData\\0002" };
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

	/*
	PACL acl = nullptr;

	SECURITY_ATTRIBUTES sa;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;

	// Call function to set the DACL. The DACL
	// is set in the SECURITY_ATTRIBUTES 
	// lpSecurityDescriptor member.
	if (!CreateMyDACL(&sa))
	{
		// Error encountered; generate message and exit.
		printf("Failed CreateMyDACL\n");
		exit(1);
	}

	BOOL IsDaclExists;
	BOOL IsDacllDefaultedMechanism;
	
	DWORD success = GetSecurityDescriptorDacl(
		sa.lpSecurityDescriptor,
		&IsDaclExists,
		&acl,
		&IsDacllDefaultedMechanism);

	if (!success)
	{
		std::cout << "GetSecurityDescriptorDacl error: " << std::system_category().message(GetLastError()) << std::endl;
		return 1;
	}

	success = SetSecurityInfo(
		myDir.GetHandle(),
		SE_FILE_OBJECT,
		DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION,
		nullptr,
		nullptr,
		acl,
		nullptr);

	if (success != ERROR_SUCCESS)
	{
		std::cout << "SetSecurityInfo error: " << std::system_category().message(GetLastError()) << std::endl;
		return 1;
	}

	// Free the memory allocated for the SECURITY_DESCRIPTOR.
	if (NULL != LocalFree(sa.lpSecurityDescriptor))
	{
		// Error encountered; generate message and exit.
		printf("Failed LocalFree\n");
		exit(1);
	}
	*/
	return 0;
}
# Windows Acl Wrapper
Written modern c++ wrapper for win32 acl methods on windows directories - can be expanded to support more objects on windows system.

The project is basically written for change Dacl/Owner of Directories - You can expand it and change also Sacl/PrimaryGroup for directories or other objects (files, namedpipes, process etc.)

This is just example project.

----
*Author*:      [Jack Abulafia](https://www.linkedin.com/in/jackabu)

## Dependencies
Aclapi.h (Win32)
Windows OS.

## Getting Started
Take a look at source.cpp
Create an instance of ProtectedDirectory (you may expanded to support more windows os objects):
```cpp
	ProtectedDirectory myDir{ L"C:\\ProgramData\\0003" };
```

Now you may modifiy your dacl/owner:
```cpp
	if (myDir.ChangeDirectoryOwner(Owner(Trustee::BuiltinAdministrators)/*WinBuiltinAdministratorsSid*//*WinLocalSystemSid*/))
	{
		std::cout << "success to change to system owner" << std::endl;
	}
```

```cpp
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
```

For more information:
https://docs.microsoft.com/en-us/windows/win32/secauthz/security-descriptor-string-format
https://docs.microsoft.com/en-us/windows/win32/api/aclapi/nf-aclapi-setsecurityinfo


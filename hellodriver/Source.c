#include "ntddk.h"

VOID Unload(IN PDRIVER_OBJECT DriverObject)
{
	DbgPrint("driver unload \r\n");
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath) // main
{
	/*
	1. UNICODE_STRING string = RTL_CONSTANT_STRING(L"hello driver\r\n");
	UNICODE_STRING string = { 0 };
	2. RtlInitUnicodeString(&string, L"hellow driver");
	======================================================================================================================
	3. WCHAR strbuf[120] = { 0 };
	string.Buffer = strbuf;
	string.Length = string.MaximumLength = wsclen(L"hello driver") * sizeof(WCHAR);
	wcscpy(string.Buffer, L"hello driver"); 
	======================================================================================================================
	deststring.Buffer = strbuf;
	deststring.Length = deststring.MaximumLength = 60;

	RtlCopyUnicodeString(&deststring, &sourcestring);
	======================================================================================================================
	RtlUpcaseUnicodeString(&deststring, &sourcestring, 1);
	RtlFreeUnicodeString(&deststring);
	*/
	DriverObject->DriverUnload = Unload;
	
	WCHAR strbuf[60] = { 0 };
	UNICODE_STRING sourcestring = RTL_CONSTANT_STRING(L"hello driver");
	ANSI_STRING deststring = { 0 };
	NTSTATUS status;

	status = RtlUnicodeStringToAnsiString(&deststring, &sourcestring, TRUE);

	if (NT_SUCCESS(status))
	{
		DbgPrint("%Z", &deststring);
		RtlFreeAnsiString(&deststring);
	}
	else if (NT_ERROR(status))
	{
		DbgPrint("STRING COPY ERROR");
		return -1;
	}

	return STATUS_SUCCESS;
}
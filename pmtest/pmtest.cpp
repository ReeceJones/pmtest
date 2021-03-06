// pmtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdio>

//const DWORD dwAllocLocation = 0x130000;
DWORD dwPid;

DWORD GetPID(const char* moduleName)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	Process32First(snapshot, &processEntry);
	do
	{
		if (!strcmp(moduleName, processEntry.szExeFile))
		{
			CloseHandle(snapshot);
			return (DWORD)processEntry.th32ProcessID;
		}
	} while (Process32Next(snapshot, &processEntry));

	CloseHandle(snapshot);
}

DWORD GetModuleAddress(const char* moduleName)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);
	MODULEENTRY32 moduleEntry;
	moduleEntry.dwSize = sizeof(MODULEENTRY32);

	Module32First(snapshot, &moduleEntry);
	do
	{
		if (!strcmp(moduleName, moduleEntry.szModule))
		{
			CloseHandle(snapshot);
			return (DWORD)moduleEntry.modBaseAddr;
		}
	} while (Module32Next(snapshot, &moduleEntry));

	CloseHandle(snapshot);
}

int main()
{
	DWORD dwAllocLocation;
	scanf_s("0x%X\n", &dwAllocLocation);

	dwPid = GetPID("maptester.exe");
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	// get the magic number
	printf("searching for magic number at 0x%X\n", dwAllocLocation);
	int magic;
	ReadProcessMemory(hProcess, (LPCVOID)dwAllocLocation, &magic, sizeof(int), nullptr);
	printf("was your magic number %d? oh yeah, the last error was 0x%X\n", magic, GetLastError());

	system("pause");

    return 0;
}


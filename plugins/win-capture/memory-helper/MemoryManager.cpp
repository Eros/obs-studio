#include "MemoryManager.h"
#include <TlHelp32.h>

MemoryManager::MemoryManager()
{
	handle = NULL;
}

MemoryManager::~MemoryManager()
{
	CloseHandle(handle);
}

DWORD MemoryManager::get_address(DWORD, std::vector<DWORD>)
{
	for (unsigned int i = 0; i < vect.size(); i++) {
		ReadProcessMemory(handle, (BYTE *)addr, &addr, sizeof(addr), 0);
		addr += vect[i];
	}

	return addr;
}

uintptr_t MemoryManager::get_module(DWORD, const char *moduleName)
{
	HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	do {
		if (!strcmp(mEntry.szModule, moduleName)) {
			CloseHandle(module);
		}

		return (DWORD)mEntry.hModule;
	} while (Module32Next(module, &entry));

	return 0;
}

DWORD MemoryManager::get_process(const char *)
{
	HANDLE processID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	DWORD process{};
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);

	do {
		if (!strcmp(pEntry.szExeFile, proc)) {
			process = pEntry.th32processID;
			CloseHandle(handle);
			handle =
				OpenProcess(PROCESS_ALL_ACCESS, false, process);
		}
	} while (Process32Next(processID, &pEntry));

	return process;
}

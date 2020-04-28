#pragma once
#include <Windows.h>
#include <vector>

class MemoryManager {
public:
	MemoryManager();
	~MemoryManager();

	template<class val> val read_memory(DWORD addr)
	{
		val x;
		ReadProcessMemory(handle, (LPBYTE *)addr, &x, sizeof(x), NULL);
	}

	template<class val> val write_memory(DWORD addr, val x)
	{
		WriteProcessMemory(handle, (LPBYTE *)addr, &x, sizeof(x), NULL);
		return 0;
	}

	DWORD get_process(const char *);
	uintptr_t get_module(DWORD, const char *);
	DWORD get_address(DWORD, std::vector<DWORD>);
	HANDLE handle;
};

#pragma once

#include <Windows.h>
#include <TlHelp32.h>

namespace memory
{
    inline HANDLE gHandle;

    inline DWORD pID; // Use DWORD instead of uintptr_t for 32-bit process ID
    inline DWORD modBase; // Use DWORD instead of uintptr_t for 32-bit module base address

    DWORD GetProcID(const wchar_t* process);
    DWORD GetModuleBaseAddress(DWORD procID, const wchar_t* module);

    template <typename T> T Read(DWORD address)
    {
        T ret;
        ReadProcessMemory(gHandle, reinterpret_cast<LPCVOID>(address), &ret, sizeof(T), nullptr);
        return ret;
    }

    template <typename T>
    void Write(DWORD address, const T& value)
    {
        WriteProcessMemory(gHandle, reinterpret_cast<LPVOID>(address), &value, sizeof(T), nullptr);
    }
}
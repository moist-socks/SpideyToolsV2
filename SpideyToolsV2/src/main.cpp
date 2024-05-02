#include <iostream>
#include <thread>
#include "memory/memory.h"

DWORD moduleBaseAddress = 0;
float x, y, z;


void setValueLoop() {
    // Read the value at the address
    DWORD valueAtAddress = memory::Read<DWORD>(moduleBaseAddress + 0x0050B480);
    if (valueAtAddress == 0)
    {
        std::cerr << "Failed to read value at address." << std::endl;
        return;
    }

    // Calculate the final addresses to write to
    DWORD addressToWriteX = valueAtAddress + 0x44;
    DWORD addressToWriteY = addressToWriteX + sizeof(float);
    DWORD addressToWriteZ = addressToWriteY + sizeof(float);

    while (true) {
        if (!GetAsyncKeyState('T')) continue;

        // Get the foreground window and its name
        HWND targetWindow = GetForegroundWindow();
        char windowName[256];
        GetWindowTextA(targetWindow, windowName, sizeof(windowName));

        // Check if the window name contains "Spider-Man"
        if (strstr(windowName, "Spider-Man") != nullptr) {
            memory::Write<float>(addressToWriteX, x);
            memory::Write<float>(addressToWriteY, y);
            memory::Write<float>(addressToWriteZ, z);
        }
    }
}
int main()
{
    const wchar_t* processName = L"SpiderMan.exe";
    const wchar_t* moduleName = L"SpiderMan.exe"; // Assuming the module name is the same as the process name

    DWORD procID = memory::GetProcID(processName);
    if (procID == 0)
    {
        std::cerr << "Failed to get process ID of SpiderMan.exe." << std::endl;
        return 1;
    }

    moduleBaseAddress = memory::GetModuleBaseAddress(procID, moduleName);
    if (moduleBaseAddress == 0)
    {
        std::cerr << "Failed to get module base address of SpiderMan.exe." << std::endl;
        return 1;
    }

    std::cout << "Process ID of SpiderMan.exe: " << procID << std::endl;
    std::cout << "Module Base Address of SpiderMan.exe: 0x" << std::hex << moduleBaseAddress << std::endl;


    std::cout << "PRESS 'T' AFTER YOU INPUT NUMBERS!" << std::endl;;

    std::thread(setValueLoop).detach();

    while (true) {
        std::cout << "\nInput X value: ";
        std::cin >> x;
        std::cout << "Input Y value: ";
        std::cin >> y;
        std::cout << "Input Z value: ";
        std::cin >> z;
    };

    return 0;
}

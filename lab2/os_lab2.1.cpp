#include <windows.h>
#include <iostream>

#define BUFF_SIZE 144

int main()
{
    std::cout << "\n==== WINDOWS INFO ====\n";
    char windows_dir[BUFF_SIZE];
    char windows_temp_dir[BUFF_SIZE];
    GetWindowsDirectoryA(windows_dir, BUFF_SIZE); 
    GetTempPathA(BUFF_SIZE, windows_temp_dir);

    std::cout << "\n Windows directory: " << windows_dir;
    std::cout << "\n Windows TEMP directory: " << windows_temp_dir;

    std::cout << "\n\n==== SYSTEM INFO ====\n";
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    std::cout << "\n Processor type: " << si.dwProcessorType;
    std::cout << "\n Cores: " << si.dwNumberOfProcessors;
    std::cout << "\n Min Adress: " << si.lpMinimumApplicationAddress;
    std::cout << "\n Max Adress: " << si.lpMaximumApplicationAddress;

    std::cout << "\n\n==== MEMORY INFO ====\n";
    LPMEMORYSTATUSEX ms;
    GlobalMemoryStatusEx(ms);
    
    std::cout << "\n Physical memory: " << ms->ullTotalPhys;
    std::cout << "\n Virtual memory: " << ms->ullTotalVirtual;

    std::cout << std::endl;
    return 0;
}





    
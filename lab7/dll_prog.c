#include <windows.h>

extern __declspec(dllexport) int a = 23;

__declspec(dllexport) int f(int b) { return b*b; }

__declspec(dllexport) int g(int b) { return b*b*b; }

BOOL WINAPI DllMain (HANDLE hModule, DWORD dwReason, LPVOID lpReserved) 
{
    return TRUE;
}
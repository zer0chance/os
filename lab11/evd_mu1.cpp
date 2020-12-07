#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "libevd1" )

HANDLE hMutex;

extern __declspec(dllimport)

char sh[6];

int main(void) {
    hMutex = CreateMutex(NULL, FALSE, (LPCSTR)"MyTestMutex");
    
    while (1) {
        WaitForSingleObject(hMutex, INFINITE);
        printf("sh: %s\n", sh);
        ReleaseMutex(hMutex);
    }
    
    CloseHandle(hMutex);
    
    return 0;
}

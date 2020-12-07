#include <windows.h>
//#include <process.h>
#include <stdio.h>

#pragma comment(lib, "libevd1" )

HANDLE hSem;

extern __declspec(dllimport)

char sh[6];

int main(void) {
    hSem = CreateSemaphore(NULL, 1, 1, (LPCSTR)"MyTestSemaphore");
    
    while (1) {
        WaitForSingleObject(hSem, INFINITE);
        printf("sh: %s\n", sh);
        ReleaseSemaphore(hSem, 1, 0);
    }
    
    CloseHandle(hSem);
    //CloseHandle(hEvent2);
    
    return 0;
}

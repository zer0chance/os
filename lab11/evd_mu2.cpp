#include <windows.h>
#include <process.h>
#include <stdio.h>

#pragma comment(lib, "libevd1" )
extern __declspec(dllimport)

char sh[6];
//HANDLE hEvent1, hEvent2;
HANDLE hMutex;

int main() {
    int counter = 0;

    hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, (LPCSTR)"MyTestMutex");
    
    while (1) {
        WaitForSingleObject(hMutex, INFINITE);
        if (counter % 2) {
            sh[0] = 'H'; sh[1] = 'e'; sh[2] = 'l'; sh[3] = 'l'; sh[4] = 'o'; sh[5] = '\0';
        } else {
            sh[0] = 'B'; sh[1] = 'y'; sh[2] = 'e'; sh[3] = '_'; sh[4] = 'u'; sh[5] = '\0';
        }
        
        ReleaseMutex(hMutex);
        counter++;
        Sleep(100);
    }
}

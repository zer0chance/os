#include <windows.h>
#include <process.h>
#include <stdio.h>

CRITICAL_SECTION cs;
char sh[6];
int counter = 0;

void Thread(void* pParams)
{   
    while (counter < 10000)
    { 
        EnterCriticalSection(&cs);
        if(counter%2) {
            sh[0] = 'H'; sh[1] = 'e'; sh[2] = 'l'; sh[3] = 'l'; sh[4] = 'o'; sh[5] = '\0';
        } else {
            sh[0] = 'B'; sh[1] = 'y'; sh[2] = 'e'; sh[3] = '_'; sh[4] = 'u'; sh[5] = '\0';
        }
        LeaveCriticalSection(&cs);
        counter++;
    }
}

int main(void)
{ 
    InitializeCriticalSection(&cs);
    
    _beginthread(Thread, 0, NULL);
    while(counter < 10000)
    {
        EnterCriticalSection(&cs);
        printf("%s\n",sh);
        LeaveCriticalSection(&cs);
        //Sleep(1);
    }
    
    return 0;
}

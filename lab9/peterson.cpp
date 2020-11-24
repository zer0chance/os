#include <windows.h>
#include <stdio.h>
#include <process.h>

void thread1();
void thread2();

typedef void (__cdecl *fun)(void*);

int sh = 0;
//int flag[2] = { 1,1 };
int main()
{
    HANDLE h[2];
    h[0] = (HANDLE) _beginthread((fun)thread1, 0, NULL);
    h[1] = (HANDLE) _beginthread((fun)thread2, 0, NULL);
    //while (flag[0] || flag[1]);
    //WaitForSingleObject(h[1], INFINITE);
    WaitForMultipleObjects(2,h,TRUE,INFINITE);

    printf("%i\n", sh);

    return 0;
}

bool readyFlags[2];
int turn;
void EnterCriticalRegion(int threadId)
{
    readyFlags [threadId] = true;  // Флаг текущего потока 
    turn = 1 - threadId;           // Флаг очереди исполнения
    
    while (turn == 1 - threadId && readyFlags [1 - threadId]);
}

void LeaveCriticalRegion(int threadId)
{
    readyFlags[threadId] = false;  // Сброс  флага текущего потока
}

void thread1()
{
    for(int i = 0; i < 10000; i++)
    {
        EnterCriticalRegion(0);
        //while(turn);
        sh++; //критическая область
        LeaveCriticalRegion(0);
        //turn=1;Sleep(10); //некритическая область
    }

    readyFlags[0] = 0;
}

void thread2()
{
    for(int i=0; i < 10000; i++)
    {
        EnterCriticalRegion(1);
        //while(!turn);
        sh+=2;  //критическая область
        LeaveCriticalRegion(1);
        //turn=0; Sleep(10); //Sleep(10000); 
        //некритическая область
    }

    readyFlags[1]=0;
}
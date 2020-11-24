// cl /MT /D "_X86_" benchmark.cpp 
#include <windows.h>
#include <process.h>
#include <iostream>
#include <chrono>

typedef void (__cdecl *fun)(void*);

#define ITERATIONS 10000

CRITICAL_SECTION cs;
char sh[10];
int turn;
int counter1 = 0;
int counter2 = 0;
bool readyFlags[2];

void EnterCriticalRegion(int threadId)
{
    readyFlags [threadId] = true;
    turn = 1 - threadId;
    
    while (turn == 1 - threadId && readyFlags [1 - threadId]);
}

void LeaveCriticalRegion(int threadId)
{
    readyFlags[threadId] = false;
}

void Thread1()
{
    while (counter1 < ITERATIONS)
    {
        EnterCriticalRegion(0);
        //Sleep(20);
        if(counter1 % 2) {
            sh[0] = '1'; 
            sh[1] = '2'; 
            sh[2] = '3'; 
            sh[3] = '4'; 
            sh[4] = '5'; 
            sh[5] = '9'; 
            sh[6] = '7'; 
            sh[7] = '8'; 
            sh[8] = '9'; 
            sh[9] = '\0';
        } else {
            sh[0] = '9'; 
            sh[1] = '8'; 
            sh[2] = '7'; 
            sh[3] = '6'; 
            sh[4] = '5'; 
            sh[5] = '4'; 
            sh[6] = '3'; 
            sh[7] = '2'; 
            sh[8] = '1'; 
            sh[9] = '\0';
        }
        counter1++;
        LeaveCriticalRegion(0); 
    }
    readyFlags[1] = 0;
}

void Thread2()
{ 
    while (counter2 < ITERATIONS)
    { 
        EnterCriticalSection(&cs);
        //Sleep(20);
        if(counter2 % 2) {
            sh[0] = '1'; 
            sh[1] = '2'; 
            sh[2] = '3'; 
            sh[3] = '4'; 
            sh[4] = '5'; 
            sh[5] = '9'; 
            sh[6] = '7'; 
            sh[7] = '8'; 
            sh[8] = '9'; 
            sh[9] = '\0';
        } else {
            sh[0] = '9'; 
            sh[1] = '8'; 
            sh[2] = '7'; 
            sh[3] = '6'; 
            sh[4] = '5'; 
            sh[5] = '4'; 
            sh[6] = '3'; 
            sh[7] = '2'; 
            sh[8] = '1'; 
            sh[9] = '\0';
        }
        counter2++;
        LeaveCriticalSection(&cs); 
    }
}

int main(void)
{
    printf("===========Peterson===========\n");
    Sleep(200);

    auto start1 = std::chrono::steady_clock::now();
    HANDLE h1 = (HANDLE) _beginthread((fun)Thread1, 0, NULL);
    while(counter1 < ITERATIONS)
    {
        EnterCriticalRegion(1);
        counter1++;
        printf("%d %s\n", counter1, sh);
        LeaveCriticalRegion(1);
    }
    WaitForSingleObject(h1, INFINITE);
    auto end1 = std::chrono::steady_clock::now();

    printf("============WinAPI============\n");
    Sleep(200);
    
    InitializeCriticalSection(&cs);

    auto start2 = std::chrono::steady_clock::now();
    HANDLE h2 = (HANDLE) _beginthread((fun)Thread2, 0, NULL);
    while(counter2 < ITERATIONS)
    {
        EnterCriticalSection(&cs);
        counter2++;
        printf("%d %s\n", counter2, sh);
        LeaveCriticalSection(&cs);
    }
    WaitForSingleObject(h2, INFINITE);
    auto end2 = std::chrono::steady_clock::now();

    auto result1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    auto result2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

    std::cout << "\nElapsed time Peterson: " << result1.count() << '\n';
    std::cout << "\nElapsed time WinAPI:   " << result2.count() << '\n';

    return 0;
}

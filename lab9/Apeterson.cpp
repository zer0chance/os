#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <process.h>
#include <chrono>
void thread1();
void thread2();
void peterson();
void winapi();
void thread_api_1(void* pParams);

typedef void(__cdecl *fun)(void*);


CRITICAL_SECTION cs;
int counter_api = 0;
int mass[9];
int main()
{
	auto begin = std::chrono::steady_clock::now();
	peterson();
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	counter_api = 0;
	auto begin2 = std::chrono::steady_clock::now();
	winapi();
	auto end2 = std::chrono::steady_clock::now();
	auto elapsed_ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2);

	std::cout << "The time Peterson: " << elapsed_ms.count() << " ms\n";
	std::cout << "The time Winapi: " << elapsed_ms2.count() << " ms\n";

    return 0;
}

bool readyFlags[2];
int turn;
int sh = 0; 

void peterson()
{
	printf("\n\nPETERSON\n\n");
	HANDLE h[2];
	h[0] = (HANDLE)_beginthread((fun)thread1, 0, NULL);
	h[1] = (HANDLE)_beginthread((fun)thread2, 0, NULL);
	WaitForMultipleObjects(2, h, TRUE, INFINITE);
//	printf("count: %i\n", counter_api);
}

void winapi()
{
	printf("\n\nWINAPI\n\n");
	InitializeCriticalSection(&cs);
	HANDLE h = (HANDLE)_beginthread(thread_api_1, 0, NULL);

	while (counter_api < 10000) {
		EnterCriticalSection(&cs);
		counter_api++;
		printf(" ");
		LeaveCriticalSection(&cs);
	}
	//printf("itog %d\n", counter_api);
	WaitForSingleObject(h, INFINITE);
	printf("\n\n\n\n");
}

void thread_api_1(void* pParams)
{
	while (counter_api < 10000) {
		EnterCriticalSection(&cs);
		counter_api++;
		printf(" ");
		LeaveCriticalSection(&cs);
	}
}

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
    while (counter_api < 10000) {
    {
        EnterCriticalRegion(0);
        //while(turn);
		counter_api++; //критическая область
		printf(" ");
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
        counter_api++;  //критическая область
		printf(" ");
        LeaveCriticalRegion(1);
        //turn=0; Sleep(10); //Sleep(10000); 
        //некритическая область
    }

    readyFlags[1]=0;
}


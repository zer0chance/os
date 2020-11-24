//  > cl /MT /D "_X86_" th4.cpp
#include <iostream>
#include <thread>
#include <windows.h>

typedef int (*fun)(char*,int* p);

int g(char* str, int* p)
{
    *p=0;
    printf("%s\n",str);
    return 0;
}

int q = 1;

void Thread(void* pg) 
{
    int counter = 0;
    while (q)
    { 
        printf("child\n");
        Sleep(10);
        if(counter++ > 1000) break;
    }

    ((fun)pg)((char*) "thread_is_over!", &q);
}

int main(void)
{
    std::thread thr(Thread, (void*)g);
    while(q) 
    {
        printf("parent %d\n", q);
        Sleep(10);
    }
    thr.join();
    return 0;
}

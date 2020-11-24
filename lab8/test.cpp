#include <iostream>
#include <thread>

int var = 0;

void foo(void)
{
    for (int i = 0; i < 100000; i++) 
    {
        var++;
        //std::cout << var << '\n';
    }
}

int main()
{
    std::thread thr1(foo);
    std::thread thr2(foo);
    std::thread thr3(foo);
    std::thread thr4(foo);
    std::thread thr5(foo);

    thr1.detach();
    thr2.detach();
    thr3.detach();
    thr4.detach();
    thr5.detach();

    std::cout << "Result: " << var << '\n';
    return 0;
}
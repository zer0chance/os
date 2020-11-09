#include <windows.h>

extern __declspec(dllimport) int a;
int f(int);
int g(int);

int main()
{
    printf("%i %i %i\n", a, f(3), g(3));

    while (1) {}

    return 0;    
}
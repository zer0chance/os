#include <windows.h>

typedef int (*fun)(int);

int main()
{
    fun pf, pg;
    int *pa;

    HINSTANCE hinst = LoadLibrary("lect_dll.dll");
    pa = (int*) GetProcAddress(hinst, "a");
    pf = (fun) GetProcAddress(hinst, "f");
    pg = (fun) GetProcAddress(hinst, "g");

    printf("a = %d\nf = %d\ng = %d", *pa, pf(3), pg(3));
    FreeLibrary(hinst);

    return 0;
}
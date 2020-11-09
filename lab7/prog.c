#include <windows.h>
#include <stdio.h>

typedef int (*fun)(int);

int main()
{
    HINSTANCE hInst = NULL;
    BOOL loaded = FALSE;
    char c = ' ';

    printf("l - load dll\n");
    printf("u - unload dll\n");
    printf("q - quit\n");

    while (1) {
        c = getch();
        
        switch (c) {
            case 'l':
                if (!loaded) {
                    hInst = LoadLibrary("dll_prog.dll");
                    loaded = TRUE;
                    printf("msg: dll is loaded\n", c);
                } else {
                    printf("warning: dll is already loaded\n", c);
                }
                break;
            case 'u':
                if (loaded) {
                    FreeLibrary(hInst);
                    loaded = FALSE;
                    printf("msg: dll is unloaded\n", c);
                } else {
                    printf("warning: dll wasn't loaded yet\n", c);
                }
                break;
            case 'q':
                if (loaded) {
                    FreeLibrary(hInst);
                    return 0;
                } else {
                    return 0;
                }
            default:
                continue;
        }
    }

    return 0;
}

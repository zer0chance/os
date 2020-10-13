#include <stdio.h>
#include <process.h>

int main()
{
    char* args[] = {"notepad", NULL};

    _spawnvp(_P_OVERLAY, args[0], args);
    //_spawnvp(_P_NOWAIT, args[0], args);

    puts("Parent process is yet running");
    return 1;
}
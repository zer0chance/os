#include <stdio.h>
#include <process.h>

int main(int argc, char** argv)
{
    char* args[] = {"cmd", "/K", "rename", argv[1], argv[2], NULL};
    if (_execvp(args[0], args) == -1) 
        perror("execv call: ");

    puts("Process wasn't created");
    return 0;
}

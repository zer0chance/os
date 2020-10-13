#include <windows.h>
#include <process.h>

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) 
{
    char* args[] = {"notepad", NULL};

    //_spawnvp(_P_OVERLAY, args[0], args);
    _spawnvp(_P_NOWAIT, args[0], args);

    MessageBox(NULL, "Parrent process is yet running.", "Message", MB_OK);
    return 1;
}
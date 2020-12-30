// > cl /MT /D "_X86_" np2.c
#include <stdio.h>
#include <windows.h>
#include <string.h>

int main() {
    HANDLE hPipe1;
    HANDLE hPipe2;
    LPTSTR lpPipeName1 = TEXT("\\\\.\\pipe\\MyPipe1");
    LPTSTR lpPipeName2 = TEXT("\\\\.\\pipe\\MyPipe2");

    char buff1[255] = " ";
    char buff2[255] = " ";
    DWORD iBytesToRead = 255;
    DWORD iBytesToWrite;

    hPipe1 = CreateFile(lpPipeName1, // имя канала
                       GENERIC_READ | // чтение и запись в канал
                       GENERIC_WRITE,
                       0, // нет разделяемых операций
                       NULL, // защита по умолчанию
                       OPEN_EXISTING, // открытие существующего канала
                       0, // атрибуты по умолчанию
                       NULL); // нет шаблона атрибутов 

    hPipe2 = CreateNamedPipe(lpPipeName2, // имя канала
                            PIPE_ACCESS_DUPLEX, // чтение и запись из канала
                            PIPE_TYPE_MESSAGE | // передача сообщений по каналу
                            PIPE_READMODE_MESSAGE | //режим чтения сообщений
                            PIPE_WAIT, // синхронная передача сообщений 
                            PIPE_UNLIMITED_INSTANCES, //число экземпляров  
                            4096, // размер выходного буфера
                            4096, // размер входного буфера
                            NMPWAIT_USE_DEFAULT_WAIT, // тайм-аут клиента 
                            NULL); // защита по умолчанию
    
    if (hPipe2 == INVALID_HANDLE_VALUE) {
        printf("CreatePipe failed: error code %d\n", (int)GetLastError());    
        return;
    }

    if((ConnectNamedPipe(hPipe2, NULL)) == 0) {
        printf("client could not connect\n");
        return;
    }
    
    while (strcmp(buff1, "q")) {
        iBytesToWrite = 255;
        iBytesToRead = 255;

        char c = getchar();
        int i = 0;
        while (c != '\n') {
            buff1[i] = c;
            i++;
            c = getchar();
        }
        
        buff1[i] = '\n';
        buff1[i + 1] = '\0';
        WriteFile(hPipe1, buff1, strlen(buff1), &iBytesToWrite, NULL);

        ReadFile(hPipe2, buff2, iBytesToRead, &iBytesToRead, NULL);
        printf("          ");
        for(i = 0; i < iBytesToRead; i++) printf("%c",buff2[i]);
    }

    CloseHandle(hPipe1);
    CloseHandle(hPipe2);
}

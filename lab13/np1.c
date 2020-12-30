// > cl /MT /D "_X86_" np1.c 
#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hPipe1;
    HANDLE hPipe2;
    LPTSTR lpPipeName1 = TEXT("\\\\.\\pipe\\MyPipe1");
    LPTSTR lpPipeName2 = TEXT("\\\\.\\pipe\\MyPipe2");

    char buff1[255] = " ";
    char buff2[255] = " ";
    DWORD iBytesToRead = 255;
    DWORD iBytesToWrite;
    
    hPipe1 = CreateNamedPipe(lpPipeName1, // имя канала
                            PIPE_ACCESS_DUPLEX, // чтение и запись из канала
                            PIPE_TYPE_MESSAGE | // передача сообщений по каналу
                            PIPE_READMODE_MESSAGE | //режим чтения сообщений
                            PIPE_WAIT, // синхронная передача сообщений 
                            PIPE_UNLIMITED_INSTANCES, //число экземпляров  
                            4096, // размер выходного буфера
                            4096, // размер входного буфера
                            NMPWAIT_USE_DEFAULT_WAIT, // тайм-аут клиента 
                            NULL); // защита по умолчанию
    
    if (hPipe1 == INVALID_HANDLE_VALUE) {
        printf("CreatePipe failed: error code %d\n", (int)GetLastError());    
        return;
    }

    if((ConnectNamedPipe(hPipe1, NULL)) == 0) {
        printf("client could not connect\n");
        return;
    }

    hPipe2 = CreateFile(lpPipeName2, // имя канала
                       GENERIC_READ | // чтение и запись в канал
                       GENERIC_WRITE,
                       0, // нет разделяемых операций
                       NULL, // защита по умолчанию
                       OPEN_EXISTING, // открытие существующего канала
                       0, // атрибуты по умолчанию
                       NULL); // нет шаблона атрибутов 

    while (1) {
        iBytesToWrite = 255;
        iBytesToRead = 255;
        printf("          ");
        ReadFile(hPipe1, buff1, iBytesToRead, &iBytesToRead, NULL);
        for(int i = 0; i < iBytesToRead; i++) printf("%c",buff1[i]);

        char c = getchar();
        int i = 0;
        while (c != '\n') {
            buff2[i] = c;
            i++;
            c = getchar();
        }
        
        buff2[i] = '\n';
        buff2[i + 1] = '\0';
        WriteFile(hPipe2, buff2, strlen(buff2), &iBytesToWrite, NULL);
    }

    CloseHandle(hPipe1);
    CloseHandle(hPipe2);
}

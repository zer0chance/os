#include <windows.h>
#include <string.h>
#include <psapi.h>

const char* ProcessName = "prog.exe";

BOOL FindProcessID(DWORD processID)
{
    char curProcessName[MAX_PATH] = "<unknown>";

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                  PROCESS_VM_READ,
                                  FALSE, processID);

    if (hProcess != NULL) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
            GetModuleBaseName(hProcess, hMod, curProcessName, sizeof(curProcessName) / sizeof(TCHAR));
        }
    }

    if (!strcmp(curProcessName, ProcessName)) {
        CloseHandle(hProcess);
        return TRUE;
    } else {
        CloseHandle(hProcess);
        return FALSE;
    }
}


int main() 
{
    HMODULE* modHndls;
    DWORD processes[1024], cbNeeded, cProcesses;
    DWORD b_alloc = 8, b_needed;
    char curProcessName[MAX_PATH];
    char modName[MAX_PATH];

    if (!EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
        printf("Failed to enumerate processes\n");
        return 1;
    }

    cProcesses = cbNeeded / sizeof(DWORD);

    DWORD pID;
    for (int i = 0; i < cProcesses; i++) {
        if(processes[i] != 0) {
            if (FindProcessID(processes[i])) {
                pID = processes[i];
                break;
            }
        }
    }

    HANDLE pHndl = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
    char c = ' ';

    printf("r - refresh process info\n");
    printf("q - quit\n");
    while (1) {
        c = getch();
        switch (c) {
            case 'r':
                printf("\n======== PROCESS INFO ========\n");
                while(1) {
                    modHndls = (HMODULE*)malloc(b_alloc);
                    EnumProcessModules(pHndl, modHndls, b_alloc, &b_needed);
                    printf("%u  %u\n", pID, pHndl);
                    printf("%u  %u\n", b_alloc, b_needed);

                    if(b_alloc >= b_needed) {
                        break;
                    }
                    else {
                        free(modHndls);
                        b_alloc = b_needed;
                    }
                }
                
                for(int i = 0; i < b_needed / sizeof(DWORD); i++) 
                {
                    GetModuleBaseName(pHndl, modHndls[i], (LPSTR)modName, sizeof(modName));
                    printf("%u\t%s", modHndls[i], modName);
                    GetModuleFileName(modHndls[i], (LPSTR)modName, sizeof(modName));
                    printf("\t%s\n", modName);
                }
                break;
            case 'q':
                CloseHandle(pHndl);
                return 0;
            default:
                continue;    
        }
    }
    
    return 0;
}

#include <windows.h>
#include <psapi.h>

int main(){
    DWORD pID;
    HANDLE pHndl;
    HMODULE* modHndls;
    DWORD b_alloc=8, b_needed;
    char modName[MAX_PATH];
    
    int i;
    
    pID=GetCurrentProcessId();
    pHndl=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pID);
    while(1){
        modHndls=(HMODULE*)malloc(b_alloc);
    
        EnumProcessModules(pHndl,modHndls,b_alloc,&b_needed);
        printf("%u  %u\n",pID,pHndl);
        printf("%u  %u\n",b_alloc, b_needed);
    
        if(b_alloc>=b_needed)
            break;
        else{
            free(modHndls);
            b_alloc=b_needed;
        }
    } 
    
    for(i=0; i<b_needed/sizeof(DWORD);i++) {
        GetModuleBaseName(pHndl, modHndls[i], (LPSTR)modName, sizeof(modName));
        printf("%u\t%s", modHndls[i],modName);
        GetModuleFileName(modHndls[i], (LPSTR)modName, sizeof(modName));
        printf("\t%s\n",modName);
    }

    return 0;
}

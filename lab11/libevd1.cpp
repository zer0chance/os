#include <windows.h>
#pragma data_seg(".M_SH")
char sh[6] = {'\0'};
#pragma data_seg()
#pragma comment(linker, "/SECTION:.M_SH,RWS")

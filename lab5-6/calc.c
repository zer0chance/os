#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "resource.h"

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	DialogBox(hInstance, (LPCTSTR)IDD_DLGTEST, NULL, (DLGPROC)DlgProc);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
	char first[100];
	char second[100]; 
	char result[100];
	char sign[2];
	int res;
	
	switch (message) 
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam) ) 
			{
				case IDC_EXIT:
					PostQuitMessage(0);
					return TRUE;
				case IDC_CALC:
					GetDlgItemText(hDlg, IDC_FIRST, first, 100);
					GetDlgItemText(hDlg, IDC_SECOND, second, 100);
					GetDlgItemText(hDlg, IDC_SIGN, sign, 2);

					if (sign[0] == '+') res = atoi(first) + atoi(second);
					else if (sign[0] == '-') res = atoi(first) - atoi(second);
					else if (sign[0] == '*') res = atoi(first) * atoi(second);
					else if (sign[0] == '/' && atoi(second) != 0) res = atoi(first) / atoi(second);
					else res = 0;

					sprintf(result, "%d", res);
					SetDlgItemText(hDlg, IDC_RESULT, result);

					HWND hWnd;
					COPYDATASTRUCT data;
					hWnd = FindWindow("Result", "Result");
					data.cbData = strlen(result);
					data.lpData = result;
					SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetFocus(), (LPARAM)&data);

					break;
			}
			break;
		case WM_COPYDATA:
			//SetWindowText(hStat, (char*)(((COPYDATASTRUCT*)lParam)->lpData));

			//char* get;
			//get = (char*)(((COPYDATASTRUCT*)lParam)->lpData);
			// char* first = strtok(get, "+-/*");
			// char* sign = strtok(NULL, "123456789");
			// char* second = strtok(NULL, "\n");
			SetDlgItemText(hDlg, IDC_FIRST, (char*)(((COPYDATASTRUCT*)lParam)->lpData));
			//SetDlgItemText(hDlg, IDC_SIGN, sign);
			//SetDlgItemText(hDlg, IDC_SECOND, second);
			//SetDlgItemText(hDlg,IDC_EDIT2,result);
			break;	
		default:
			return FALSE;
	}
}

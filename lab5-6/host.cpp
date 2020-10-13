#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK MyWndProc(HWND, UINT, WPARAM,
                           LPARAM);
HDC hdc;
RECT rt;
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	LPCSTR lpszAppName="Host";
	BOOL ret;

	wc.lpszClassName = lpszAppName;
	wc.hInstance=hInstance;
	wc.lpfnWndProc = (WNDPROC)MyWndProc;

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.hIcon = 0;

	wc.lpszMenuName = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if(!RegisterClass(&wc))
		return 0;
	hWnd = CreateWindow( lpszAppName,
	                     lpszAppName,
	                     WS_OVERLAPPEDWINDOW,
	                     100,
	                     100,
	                     200,
	                     130,
	                     NULL,
	                     NULL,
	                     hInstance,
	                     NULL);
	ShowWindow(hWnd, SW_SHOWNORMAL);

	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
LRESULT CALLBACK
MyWndProc(HWND hWnd, UINT message,
          WPARAM wParam,
          LPARAM lParam) {
	PAINTSTRUCT ps;
	HINSTANCE hInst;
	
	static HWND hBtn;
	static HWND hEdt1, hEdt2;
	static HWND hStat;
	TCHAR StrA[20];
	int a, b, sum, Len;
	switch (message) {
		case WM_CREATE:
			hInst = ((LPCREATESTRUCT)lParam)->hInstance;
			hStat = CreateWindow("static", "0", WS_CHILD | WS_VISIBLE,
			                     60, 0, 120, 20, hWnd, 0, hInst, NULL);
			ShowWindow(hStat, SW_SHOWNORMAL);
			hEdt1 = CreateWindow("edit", "0", WS_CHILD | WS_VISIBLE,
			                     60, 30, 120, 50, hWnd, 0, hInst, NULL);
			hEdt2 = CreateWindow("edit", "0", WS_CHILD | WS_VISIBLE,
			                     60, 70, 120, 90, hWnd, 0, hInst, NULL);
			hBtn = CreateWindow("button", "Send", WS_CHILD | WS_VISIBLE,
			                     60, 100, 120, 110, hWnd, 0, hInst, NULL);
			ShowWindow(hStat, SW_SHOWNORMAL);
			break;
		case WM_COMMAND:
			if (lParam == (LPARAM)hBtn)
			{
				HWND hWndClient = FindWindow(NULL,"Dialog");
				COPYDATASTRUCT data, data2;
				char result[100], result2[100];
				GetWindowText(hEdt1, result, 100);		
				data.cbData=strlen(result);
				data.lpData=result;
				SendMessage (hWndClient, WM_COPYDATA, (WPARAM)GetFocus(),
					            (LPARAM)&data);
				/*GetWindowText(hEdt1, result2, 100);		
				data2.cbData=strlen(result2);
				data2.lpData=result2;
				SendMessage (hWndClient, WM_COPYDATA, (WPARAM)GetFocus(),
					            (LPARAM)&data2);*/
			}
			break;
		case WM_COPYDATA:
			SetWindowText(hStat, (char*)(
			                  ((COPYDATASTRUCT*)lParam)->lpData));
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rt);
			DrawText(hdc, "Result: ", strlen("Result: "), &rt,
			         DT_LEFT);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


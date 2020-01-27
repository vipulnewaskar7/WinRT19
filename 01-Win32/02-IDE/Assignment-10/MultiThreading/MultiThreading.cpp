#include<windows.h>

DWORD WINAPI ThreadProc1(LPVOID);
DWORD WINAPI ThreadProc2(LPVOID);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hWnd;
	TCHAR AppName[] = TEXT("MultiThreadingApp");
	MSG msg;

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = AppName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(AppName,
		TEXT("MultiThreading App"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;
	TCHAR str[] = TEXT("Info");
	switch (iMsg)
	{
		case WM_CREATE:
			hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProc1, (LPVOID)hWnd, 0, NULL);
			hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadProc2, (LPVOID)hWnd, 0, NULL);
			break;
		case WM_LBUTTONDOWN:
			MessageBox(hWnd, TEXT("Click Event..."), str, MB_OK);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProc1(LPVOID param)
{
	HDC hdc;
	HWND hWnd = (HWND)param;
	unsigned long int i;
	TCHAR str[255];
	hdc = GetDC(hWnd);
	for (i = 0; i < 4294967295; i++)
	{
		wsprintf(str, TEXT("Thread 1 -> Increasing Order : %u"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}
	ReleaseDC(hWnd, hdc);
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID param)
{
	HDC hdc;
	HWND hWnd = (HWND)param;
	unsigned long int i;
	TCHAR str[255];
	hdc = GetDC(hWnd);
	for (i = 4294967295; i>0; i--)
	{
		wsprintf(str, TEXT("Thread 2 -> Decreasing Order : %u"), i);
		TextOut(hdc, 5, 100, str, wcslen(str));
	}
	ReleaseDC(hWnd, hdc);
	return 0;
}



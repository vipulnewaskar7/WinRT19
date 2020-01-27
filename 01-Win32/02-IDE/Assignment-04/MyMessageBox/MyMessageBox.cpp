#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hWnd;
	MSG msg;
	TCHAR lpszClassName[] = TEXT("MyMessageBox");
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpszClassName = lpszClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW ;
	wndClass.lpfnWndProc = WndProc;
	
	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(lpszClassName, 
		TEXT("My MessageBox"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)(msg.wParam));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
		case WM_CREATE:
			MessageBox(hwnd, TEXT("ON CREATE CALLED..."), TEXT("My MessageBox"), MB_OK);
			break;

		case WM_DESTROY:
			MessageBox(hwnd, TEXT("ON DESTROY CALLED, BYE..."), TEXT("My MessageBox"), MB_OK);
			PostQuitMessage(0);
			break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}




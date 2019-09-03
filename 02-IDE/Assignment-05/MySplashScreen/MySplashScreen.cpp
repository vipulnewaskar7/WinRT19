#include<windows.h>
#include "MySplashScreen.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hWnd;
	MSG msg;
	TCHAR lpszAppName[] = TEXT("My Splash Screen");
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndClass.hCursor = LoadCursor(hInstance, IDC_WAIT);
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = lpszAppName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(lpszAppName,
		TEXT("My Splash Screen"),
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
	static HINSTANCE hInstance;
	RECT rect;
	BITMAP bitmap;
	static HBITMAP hBitmap;
	HDC hdc, cdc;
	PAINTSTRUCT paintStruct;
	switch(iMsg)
	{
		case WM_CREATE:
			hInstance = GetModuleHandle(NULL);
			hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &paintStruct);
			GetClientRect(hWnd, &rect);
			cdc = CreateCompatibleDC(hdc);
			SelectObject(cdc, hBitmap);
			GetObject(hBitmap, sizeof(BITMAP), &bitmap);
			StretchBlt(hdc, 0, 0, rect.right, rect.bottom, cdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
			DeleteObject(cdc);
			EndPaint(hWnd, &paintStruct);
			break;
	}
	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}




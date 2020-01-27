#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wndClass;
	MSG msg;
	TCHAR AppName[] = TEXT("HelloWorldApp");
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = AppName;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpszMenuName = NULL;
	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(AppName,
		TEXT("Hello World Application"),
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

	while (GetMessage(&msg, NULL, 0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RECT rect;
	PAINTSTRUCT paintStruct;
	switch (iMsg)
	{
		case WM_CREATE:
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &paintStruct);
			GetClientRect(hWnd, &rect);
			SetTextColor(hdc, RGB(0, 255, 0));
			SetBkColor(hdc, RGB(0, 0, 0));
			DrawText(hdc, TEXT("Hello World..."), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &paintStruct);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}




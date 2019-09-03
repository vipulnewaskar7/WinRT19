#include<windows.h>
#define MYTIMER 201

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndClass;
	HWND hWnd;
	MSG msg;
	TCHAR AppName[] = TEXT("Strips");

	wndClass.hInstance = hInstance;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = AppName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(AppName,
		TEXT("Strips"),
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
	HDC hdc;
	static RECT rect, rect_temp;
	HBRUSH hBrush;
	PAINTSTRUCT paintStruct;
	static int iPaintFlag = 0;
	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hWnd, MYTIMER, 2000, NULL);
		break;
	case WM_TIMER:
		KillTimer(hWnd, MYTIMER);
		if (iPaintFlag >= 8)
		{
			iPaintFlag = 0;
		}

		SetTimer(hWnd, MYTIMER, 2000, NULL);
		rect_temp.left = rect.left + iPaintFlag * (rect.right - rect.left) / 8;
		rect_temp.top = rect.top;
		rect_temp.bottom = rect.bottom;
		rect_temp.right = rect_temp.left + (rect.right - rect.left) / 8;

		InvalidateRect(hWnd, &rect_temp, TRUE);
		iPaintFlag++;
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &rect);
		hdc = BeginPaint(hWnd, &paintStruct);
		switch (iPaintFlag)
		{
		case 0:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		case 8:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		default:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rect_temp, hBrush);
			break;
		}
		EndPaint(hWnd, &paintStruct);
		break;
	case WM_CHAR:
		switch (LOWORD(wParam))
		{
		case 'R':
		case 'r':
			iPaintFlag = 1;
			break;
		case 'G':
		case 'g':
			iPaintFlag = 2;
			break;
		case 'B':
		case 'b':
			iPaintFlag = 3;
			break;
		case 'C':
		case 'c':
			iPaintFlag = 4;
			break;
		case 'M':
		case 'm':
			iPaintFlag = 5;
			break;
		case 'Y':
		case 'y':
			iPaintFlag = 6;
			break;
		case 'K':
		case 'k':
			iPaintFlag = 7;
			break;
		case 'W':
		case 'w':
			iPaintFlag = 8;
			break;
		default:
			iPaintFlag = 0;
			break;
		}
		InvalidateRect(hWnd, &rect, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMsg, wParam, lParam));
}



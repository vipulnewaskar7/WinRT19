#include<windows.h>
#include<stdio.h>
#include"IClassFactoryAutomationClient.h"
void ComErrorDescriptionString(HWND, HRESULT);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

IMyMath *pIMyMath = NULL;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wndclass;
	MSG msg;
    HRESULT hr;
    hr = CoInitialize(NULL);
    if(FAILED(hr))
    {
        MessageBox(NULL, TEXT("COM Library cannot be initialized, exiting..."), TEXT("PROGRAM ERROR"), MB_OK);
        exit (0);
    }
	TCHAR AppName[] = TEXT("My COM Client");
	wndclass.hInstance = hInstance;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	
	RegisterClassEx(&wndclass);

	hWnd = CreateWindow(AppName,
		TEXT("My COM Client"),
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
    CoUninitialize();
	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam,LPARAM lParam)
{
    HRESULT hr;
    int iNum1, iNum2, iNum3;
    TCHAR str [255];
	switch (iMsg)
	{
		case WM_CREATE:
        hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IMyMath, (void **)&pIMyMath);
        if(FAILED(hr))
        {
			ComErrorDescriptionString(hWnd, hr);
            DestroyWindow(hWnd);
        }
        iNum1 = 550;
        iNum2 = 450;
        pIMyMath->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
        wsprintf(str, TEXT("Sum of %d and %d is %d"),iNum1, iNum2, iNum3);
        MessageBox(hWnd, str, TEXT("Answer of Summation"),MB_OK);
        
        pIMyMath->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
        wsprintf(str, TEXT("Difference between %d and %d is %d"),iNum1, iNum2, iNum3);
        MessageBox(hWnd, str, TEXT("Answer of Subtraction"),MB_OK);
        DestroyWindow(hWnd);
        break;
        case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];
	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
	{
		hr = HRESULT_CODE(hr);
	}
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		swprintf_s(str, TEXT("[Could not find a description for error # % #x.]\n"), hr);
	}
	MessageBox(hwnd, str, TEXT("COM Error, debug"), MB_OK);
}

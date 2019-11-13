#include<windows.h>
#include "ClientOfAggregationComponentWithRegFile.h"

// Callback declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Global Variable Declaration
ISum *pISum = NULL;
ISubtract *pISubtraction = NULL;
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	// Variable Declaration
	WNDCLASSEX wndClass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("COM Aggregation Clinet");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library cannot be initiated, Program will exit now."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	// Initialize wndClass
	wndClass.cbSize = sizeof(wndClass);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = AppName;
	wndClass.lpszMenuName = NULL;

	// Register Window Class
	RegisterClassEx(&wndClass);

	hwnd = CreateWindow(AppName,
		TEXT("Client of COM dll Server"),
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
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	// Message Loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// COM Engine Uninitializing
	CoUninitialize();
	return ((int)msg.wParam);
}

// Window Procedure

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HRESULT hr;
	int iNum1, iNum2, iNum3;
	TCHAR str[255];
	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, TEXT("Program started now"), TEXT("Debug"), MB_OK);

		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface cannot be found, program will exit now."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		iNum1 = 80;
		iNum2 = 20;
		
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("Answer of Sum"), MB_OK);

		pISum->QueryInterface(IID_ISubtract, (void**)&pISubtraction);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtraction Interface cannot be found, program will exit now."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;
		pISubtraction->SubtractionOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("Answer of Subtraction"), MB_OK);

		pISubtraction->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface cannot be found, program will exit now."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISubtraction->Release();
		pISubtraction = NULL;
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Multiplication of %d and %d is %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("Answer of Multiplication"), MB_OK);

		pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface cannot be found, program will exit now."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}
		pIMultiplication->Release();
		pIMultiplication = NULL;
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iNum3);
		wsprintf(str, TEXT("Division of %d and %d is %d"), iNum1, iNum2, iNum3);
		MessageBox(hwnd, str, TEXT("Answer of Division"), MB_OK);

		pIDivision->Release();
		pIDivision = NULL;
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}




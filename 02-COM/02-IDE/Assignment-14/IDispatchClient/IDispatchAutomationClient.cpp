#include<windows.h>
#include<stdio.h>
#include"AutomationServerWithRegFile.h"
void ComErrorDescriptionString(HWND, HRESULT);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wndclass;
	MSG msg;
	HRESULT hr;
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HRESULT hr;
	int iNum1, iNum2;
	TCHAR str[255];

	IDispatch *pIDispatch = NULL;
	DISPID dispid;
	OLECHAR *szSumFunctionName = L"SumOfTwoIntegers";
	OLECHAR *szSubtractionFunctionName = L"SubtractionOfTwoIntegers";
	VARIANT vArg[2], vRet;
	DISPPARAMS param = { vArg ,0,2,NULL};

	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoInitialize(NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hWnd, hr);
			MessageBox(NULL, TEXT("COM Library cannot be initialized, exiting..."), TEXT("PROGRAM ERROR"), MB_OK);
			DestroyWindow(hWnd);
			exit(0);
		}
		iNum1 = 550;
		iNum2 = 450;
		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IMyMath, (void **)&pIDispatch);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hWnd, hr);
			MessageBox(NULL, TEXT("Component cannot be initialized, exiting..."), TEXT("COM ERROR"), MB_OK);
			DestroyWindow(hWnd);
		}
		VariantInit(vArg);
		vArg[0].vt = VT_INT;
		vArg[1].vt = VT_INT;
		vArg[0].intVal = iNum2;
		vArg[1].intVal = iNum1;
		param.cArgs = 2;
		param.cNamedArgs=0;
		param.rgdispidNamedArgs = NULL;
		param.rgvarg = vArg;
		VariantInit(&vRet);
		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szSumFunctionName, 1, GetUserDefaultLCID(), &dispid);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hWnd, hr);
			MessageBox(NULL, TEXT("Cannot get ID for SumOfTwoIntegers Function, exiting..."), TEXT("COM ERROR"), MB_OK);
			pIDispatch->Release();
			DestroyWindow(hWnd);
		}
		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &param, &vRet, NULL, NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hWnd, hr);
			MessageBox(NULL, TEXT("Cannot invoke function, exiting..."), TEXT("COM ERROR"), MB_OK);
			pIDispatch->Release();
			DestroyWindow(hWnd);
		}
		else 
		{
			wsprintf(str, TEXT("Sum of  %d and %d is %d"), iNum1, iNum2, vRet.lVal);
			MessageBox(hWnd, str, TEXT("Answer of Summation"), MB_OK);
		}
		//Subtraction
		
		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szSubtractionFunctionName, 1, GetUserDefaultLCID(), &dispid);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hWnd, hr);
			MessageBox(NULL, TEXT("Cannot get ID for SubtractionOfTwoIntegers Function, exiting..."), TEXT("COM ERROR"), MB_OK);
			pIDispatch->Release();
			DestroyWindow(hWnd);
		}
		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &param, &vRet, NULL, NULL);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(hWnd, hr);
			MessageBox(NULL, TEXT("Cannot invoke function, exiting..."), TEXT("COM ERROR"), MB_OK);
			pIDispatch->Release();
			DestroyWindow(hWnd);
		}
		else
		{
			wsprintf(str, TEXT("Subtraction of  %d and %d is %d"), iNum1, iNum2, vRet.lVal);
			MessageBox(hWnd, str, TEXT("Answer of Subtraction"), MB_OK);
		}
		
		VariantClear(vArg);
		VariantClear(vArg);
		pIDispatch->Release();
		pIDispatch = NULL;
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		CoUninitialize();
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

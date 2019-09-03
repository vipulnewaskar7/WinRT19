#include<windows.h>

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dWReason, LPVOID lpReserved)
{
	switch (dWReason)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
		default:
			break;
	}
	return TRUE;
}

extern "C" int MakeSquare(int num)
{
	return (num * num);
}

extern "C" BOOL IsNegative(int num)
{
	if (num < 0)
	{
		return TRUE;
	}
	return FALSE;
}



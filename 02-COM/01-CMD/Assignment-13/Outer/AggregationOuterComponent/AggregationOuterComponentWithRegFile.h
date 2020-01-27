#include<windows.h>
class ISum : public IUnknown
{
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract : public IUnknown
{
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// CSumSubtract Class CLSID {CC75C299-9368-4C79-966C-BEFF5B74A60D}
const CLSID CLSID_SumSubtract =
{ 0xcc75c299, 0x9368, 0x4c79,{ 0x96, 0x6c, 0xbe, 0xff, 0x5b, 0x74, 0xa6, 0xd } };

// ISum Interface IID {30B3AED2-CDC3-4D09-83C3-1B1574215FCC}
const CLSID IID_ISum =
{ 0x30b3aed2, 0xcdc3, 0x4d09,{ 0x83, 0xc3, 0x1b, 0x15, 0x74, 0x21, 0x5f, 0xcc } };

// ISubtract Interface IID {4E5832DC-AC9D-4A08-92D5-2933963ABC98}
const CLSID IID_ISubtract =
{ 0x4e5832dc, 0xac9d, 0x4a08,{ 0x92, 0xd5, 0x29, 0x33, 0x96, 0x3a, 0xbc, 0x98 } };



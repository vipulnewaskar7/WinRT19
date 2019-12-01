#include<windows.h>
class IMyMath : public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};
//CLSID of MyMath Component : {0411A7B7-63F9-46EC-A39A-EC5E322A8D77}
const CLSID CLSID_MyMath =
{ 0x0411a7b7, 0x63f9, 0x46ec,{ 0xa3, 0x9a, 0xec, 0x5e, 0x32, 0x2a, 0x8d, 0x77 } };

//IID of IMyMath Interface : {E330537F-C076-4794-BD73-8FD42AC9804A}
const IID IID_IMyMath =
{ 0xe330537f, 0xc076, 0x4794,{ 0xbd, 0x73, 0x8f, 0xd4, 0x2a, 0xc9, 0x80, 0x4a } };
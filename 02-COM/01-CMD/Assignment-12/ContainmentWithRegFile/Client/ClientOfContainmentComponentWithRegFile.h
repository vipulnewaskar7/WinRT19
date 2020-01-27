#include<windows.h>
class ISummation:public IUnknown
{
    public:
    virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*)=0;
};
class ISubtraction: public IUnknown 
{
    public:
    virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*)=0;
};
class IMultiplication: public IUnknown
{
    public:
    virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*)=0;
};
class IDivision: public IUnknown
{
    public:
    virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*)=0;
};

// CLSID of Calculator Component {029D7BFF-D359-4033-B86C-40CBC8E79B38}
const CLSID CLSID_Calculator = {0x29d7bff, 0xd359, 0x4033, 0xb8, 0x6c, 0x40, 0xcb, 0xc8, 0xe7, 0x9b, 0x38};

// IID of ISummation Interface {DD6C2E59-9B36-4843-BAC4-6241757C0858}
const IID IID_ISummation = {0xdd6c2e59, 0x9b36, 0x4843, 0xba, 0xc4, 0x62, 0x41, 0x75, 0x7c, 0x8, 0x58};

// IID of ISubtraction Interface {BC251467-ADC3-4691-9E30-F110A6FA6D37}
const IID IID_ISubtraction = {0xbc251467, 0xadc3, 0x4691, 0x9e, 0x30, 0xf1, 0x10, 0xa6, 0xfa, 0x6d, 0x37};

// IID of IMultiplication Interface {F2302C17-516A-4ECF-9092-A215E89CE96C}
const IID IID_IMultiplication = {0xf2302c17, 0x516a, 0x4ecf, 0x90, 0x92, 0xa2, 0x15, 0xe8, 0x9c, 0xe9, 0x6c};

// IID of IDivision Interface {5B4CF0A2-2181-4968-92B1-80C622285974}
const IID IID_IDivision = {0x5b4cf0a2, 0x2181, 0x4968, 0x92, 0xb1, 0x80, 0xc6, 0x22, 0x28, 0x59, 0x74};



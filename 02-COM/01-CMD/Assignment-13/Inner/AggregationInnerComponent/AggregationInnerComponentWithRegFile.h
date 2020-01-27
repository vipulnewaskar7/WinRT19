#include<windows.h>
class IMultiplication:public IUnknown
{
    public:
    virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int*)=0;
};

class IDivision:public IUnknown
{
    public:
    virtual HRESULT __stdcall DivisionOfTwoIntegers(int,int,int*)=0;
};

// CLSID of MultiplicationDivision Component {AB94BBA5-4546-42C8-B134-51359122CAC7}
const CLSID CLSID_MultiplicationDivision = 
{0xab94bba5, 0x4546, 0x42c8, 0xb1, 0x34, 0x51, 0x35, 0x91, 0x22, 0xca, 0xc7};

// IID of IMultiplication Interface {42DC664A-1268-4951-A224-CD64796507B4}
const IID IID_IMultiplication = 
{ 0x42dc664a, 0x1268, 0x4951, 0xa2, 0x24, 0xcd, 0x64, 0x79, 0x65, 0x7, 0xb4};

// IID of IDivision Interface {AA952FC2-1E8F-49EB-8FF0-BF0E19A600EA}
const IID IID_IDivision = 
{ 0xaa952fc2, 0x1e8f, 0x49eb, 0x8f, 0xf0, 0xbf, 0xe, 0x19, 0xa6, 0x0, 0xea};


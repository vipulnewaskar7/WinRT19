class ISummation : public IUnknown
{
    public:
     virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;
};

class ISubtraction : public IUnknown
{
    public:
        virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;
};

// CLSID of SumSubtract Component {B3356A50-E05F-44E8-819B-27092681FC96}
const CLSID CLSID_SumSubtract = {0xb3356a50, 0xe05f, 0x44e8, 0x81, 0x9b, 0x27, 0x9, 0x26, 0x81, 0xfc, 0x96};

// IID of ISummation Interface {DD6C2E59-9B36-4843-BAC4-6241757C0858}
const IID IID_ISummation = {0xdd6c2e59, 0x9b36, 0x4843, 0xba, 0xc4, 0x62, 0x41, 0x75, 0x7c, 0x8, 0x58};

// IID of ISubtraction Interface {BC251467-ADC3-4691-9E30-F110A6FA6D37}
const IID IID_ISubtraction = {0xbc251467, 0xadc3, 0x4691, 0x9e, 0x30, 0xf1, 0x10, 0xa6, 0xfa, 0x6d, 0x37};


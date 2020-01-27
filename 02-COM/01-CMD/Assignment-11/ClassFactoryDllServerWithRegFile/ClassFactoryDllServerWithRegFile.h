class ISum : public IUnknown
{
    public:
     virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;
};

class ISubtract : public IUnknown
{
    public:
        virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;
};

// CLSID of SumSubtract Component {B3356A50-E05F-44E8-819B-27092681FC96}
const CLSID CLSID_SumSubtract = 
{0xb3356a50, 0xe05f, 0x44e8, 0x81, 0x9b, 0x27, 0x9, 0x26, 0x81, 0xfc, 0x96};

// IID of ISum Interface {568FFA64-49DC-44A1-AEEA-A5FB54798541}
const IID IID_ISum =  
{0x568ffa64, 0x49dc, 0x44a1, 0xae, 0xea, 0xa5, 0xfb, 0x54, 0x79, 0x85, 0x41};

// IID of ISubtract Component {1433EC68-32E8-489D-80D2-6D56F2156E57}
const IID IID_ISubtract = 
{0x1433ec68, 0x32e8, 0x489d, 0x80, 0xd2, 0x6d, 0x56, 0xf2, 0x15, 0x6e, 0x57};



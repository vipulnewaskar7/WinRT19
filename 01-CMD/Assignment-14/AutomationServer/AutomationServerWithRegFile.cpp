#include<windows.h>
#include<stdio.h>
#include"AutomationServerWithRegFile.h"

class CMyMath : public IMyMath
{
    private:
        long m_cRef;
        ITypeInfo *m_pITypeInfo;
    public:
        //Constructor method declaration
        CMyMath(void);
        ~CMyMath(void);
        
        // IUnknown Specific Methods Declaration
        HRESULT __stdcall QueryInterface(REFIID, void**);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);
        
        //IDispatch Specific Methods Declaration
        HRESULT __stdcall GetTypeInfoCount(UINT*);
        HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
        HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
        HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

        // Addition and Subtraction methods' declarations
        HRESULT __stdcall SumOfTwoIntegers(int,int,int *);
        HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int*);

        HRESULT InitInstance(void);
        
};

//ClassFactory Definition
class CMyMathClassFactory: public IClassFactory
{
    private:
        long m_cRef;
    public:
        CMyMathClassFactory(void);
        ~CMyMathClassFactory(void);
        //IUnknowm interface specific methods' declarations
        HRESULT __stdcall QueryInterface(REFIID, void **);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);
        //ClassFactory interface specific methods' declarations
        HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
        HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents=0;
long glNumberOfServerLocks=0;

// AutomationServer Lib ID : {7F0DB69F-9F62-4368-AD38-DE028E906187}
const GUID LIBID_AutomationServer = 
{ 0x7f0db69f, 0x9f62, 0x4368, { 0xad, 0x38, 0xde, 0x2, 0x8e, 0x90, 0x61, 0x87 } };

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
    switch(dwReason)
    {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
	return (TRUE);
}

CMyMath::CMyMath(void)
{
    m_cRef = 1;
    InterlockedIncrement(&glNumberOfActiveComponents);
}

CMyMath::~CMyMath(void)
{
    m_pITypeInfo->Release();
    m_pITypeInfo = NULL;
    InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CMyMath::QueryInterface(REFIID riid, void **ppv)
{
    if(riid== IID_IUnknown )
    {
        *ppv = static_cast<IMyMath *>(this);
    }
    else if(riid == IID_IDispatch)
    {
        *ppv = static_cast<IMyMath *>(this);
    }
    else if(riid == IID_IMyMath)
    {
        *ppv = static_cast<IMyMath *>(this);
    }
    else
    {
        *ppv = NULL;
        return (E_NOINTERFACE);
    }
    reinterpret_cast<IUnknown *>(*ppv)->AddRef();
    return (S_OK);
}

ULONG CMyMath::AddRef(void)
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CMyMath::Release(void)
{
    InterlockedDecrement(&m_cRef);
    if(m_cRef == 0)
    {
        delete(this);
        return 0;
    }
    return m_cRef;
}

HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
    *pSum = num1 + num2;
    return (S_OK);
}

HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
    *pSubtract = num1 - num2;
    return (S_OK);
}

HRESULT CMyMath::InitInstance(void)
{
    //function declarations
    void ComErrorDescriptionString(HWND, HRESULT);
    
    HRESULT hr;
    ITypeLib *pITypeLib = NULL;

    if(m_pITypeInfo == NULL)
    {
        hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, 0x00, &pITypeLib);
        if(FAILED(hr))
        {
            ComErrorDescriptionString(NULL, hr);
            return hr;
        }

        hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
        
        if(FAILED(hr))
        {
            ComErrorDescriptionString(NULL, hr);
            pITypeLib->Release();
            return hr;
        }
        pITypeLib->Release();
    }
    return(S_OK);  
}

HRESULT CMyMathClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    CMyMath *pCMyMath=NULL;
    HRESULT hr;
    if (pUnkOuter!=NULL)
    {
        return(CLASS_E_NOAGGREGATION);
    }
	pCMyMath = new CMyMath;

    if(pCMyMath == NULL)
    {
        return (E_OUTOFMEMORY);
    }
    pCMyMath->InitInstance();

    hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
    return hr;
}

//Co-class constructor/destructor/methods end here

//ClassFactory constructor/destructor/methods start here
CMyMathClassFactory::CMyMathClassFactory(void)
{
    m_cRef=1;
}

CMyMathClassFactory::~CMyMathClassFactory(void)
{

}

ULONG CMyMathClassFactory::Release(void)
{
    InterlockedDecrement(&m_cRef);
    if(m_cRef==0)
    {
        delete(this);
        return (0);
    }
    return (m_cRef); 
}

HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void **ppv)
{
    if(riid == IID_IUnknown)
    {
        *ppv=static_cast<IClassFactory *>(this);
    }
    else if (riid == IID_IClassFactory)
    {
        *ppv=static_cast<IClassFactory *>(this);
    }
    else 
    {
        *ppv=NULL;
        return (E_NOINTERFACE);
    }
    reinterpret_cast<IUnknown *> (*ppv)->AddRef();
    return (S_OK);
}

ULONG CMyMathClassFactory::AddRef(void)
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
{
    if(fLock)
    {
        InterlockedIncrement(&glNumberOfServerLocks);
    }
    else
    {
        InterlockedDecrement(&glNumberOfServerLocks);
    }
    return (S_OK);
}

HRESULT CMyMath::GetTypeInfoCount(UINT *pCountTypeInfo)
{
    *pCountTypeInfo = 1;
    return(S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo **ppITypeInfo)
{
    *ppITypeInfo = NULL;
    if(iTypeInfo != 0)
    {
        return(DISP_E_BADINDEX);
    }
    m_pITypeInfo->AddRef();
    *ppITypeInfo = m_pITypeInfo;
    return (S_OK);
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, 
DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    HRESULT hr;
    hr = DispInvoke(this, 
        m_pITypeInfo, 
        dispIdMember,
        wFlags,
        pDispParams,
        pVarResult,
        pExcepInfo,
        puArgErr);

    return hr;
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CMyMathClassFactory *pCMyMathClassFactory=NULL;
    HRESULT hr;
    if(rclsid != CLSID_MyMath)
    {
        return (CLASS_E_CLASSNOTAVAILABLE);
    }
    pCMyMathClassFactory = new CMyMathClassFactory;
    if(pCMyMathClassFactory == NULL)
    {
        return (E_OUTOFMEMORY);
    }
    hr = 
}
#include<windows.h>
#include "ContainmentInnerComponentWithRegFile.h"
//Co-Class Definition
class CSumSubtract: public ISummation, ISubtraction
{
    private:
        long m_cRef;
    public:
        CSumSubtract(void);
        ~CSumSubtract(void);
        //IUnknowm interface specific methods' declarations
        HRESULT __stdcall QueryInterface(REFIID, void **);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);
        // Addition and Subtraction methods' declarations
        HRESULT __stdcall SumOfTwoIntegers(int,int,int *);
        HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int*);
};

//ClassFactory Definition
class CSumSubtractClassFactory: public IClassFactory
{
    private:
        long m_cRef;
    public:
        CSumSubtractClassFactory(void);
        ~CSumSubtractClassFactory(void);
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

//Co-class constructor/destructor/methods start here

CSumSubtract::CSumSubtract(void)
{
    m_cRef = 1;
    InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubtract::~CSumSubtract(void)
{
    InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
    if(riid== IID_IUnknown )
    {
        *ppv = static_cast<ISummation *>(this);
    }
    else if(riid == IID_ISummation)
    {
        *ppv = static_cast<ISummation *>(this);
    }
    else if(riid == IID_ISubtraction)
    {
        *ppv = static_cast<ISubtraction *>(this);
    }
    else
    {
        *ppv = NULL;
        return (E_NOINTERFACE);
    }
    reinterpret_cast<IUnknown *>(*ppv)->AddRef();
    return (S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CSumSubtract::Release(void)
{
    InterlockedDecrement(&m_cRef);
    if(m_cRef == 0)
    {
        delete(this);
        return 0;
    }
    return m_cRef;
}

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
    *pSum = num1 + num2;
    return (S_OK);
}

HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtract)
{
    *pSubtract = num1 - num2;
    return (S_OK);
}

//Co-class constructor/destructor/methods end here

//ClassFactory constructor/destructor/methods start here
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
    m_cRef=1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{

}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
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

ULONG CSumSubtractClassFactory::AddRef(void)
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
    InterlockedDecrement(&m_cRef);
    if(m_cRef==0)
    {
        delete(this);
        return (0);
    }
    return (m_cRef); 
}

HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    CSumSubtract *pCSumSubtract=NULL;
    HRESULT hr;
    if (pUnkOuter!=NULL)
    {
        return(CLASS_E_NOAGGREGATION);
    }
	pCSumSubtract = new CSumSubtract;
    hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
    return hr;
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
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

//ClassFactory constructor/destructor/methods end here

//Global methods to be exported outside
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CSumSubtractClassFactory *pCSumSubtractClassFactory=NULL;
    HRESULT hr;
    pCSumSubtractClassFactory = new CSumSubtractClassFactory;
    if(pCSumSubtractClassFactory==NULL)
    {
        return NULL;
    }
    hr = pCSumSubtractClassFactory->QueryInterface(riid,ppv);
    pCSumSubtractClassFactory->Release();
    return hr;
}

HRESULT __stdcall DllCanUnloadNow(void)
{
    if(glNumberOfServerLocks==0 && glNumberOfActiveComponents==0)
    {
        return (S_OK);
    }
    else
    {
        return (S_FALSE);
    }
}






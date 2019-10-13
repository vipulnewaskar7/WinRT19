#include<windows.h>
#include "ContainmentOuterComponentWithRegFile.h"
#include "ContainmentInnerComponentWithRegFile.h"
class CCalculator:public ISummation, ISubtraction, IMultiplication, IDivision
{
    private:
        long m_cRef;
        ISummation *m_pISummation;
        ISubtraction *m_pISubtraction;
    public:
        CCalculator(void);
        ~CCalculator(void);
        // IUnknown specific methods
        HRESULT __stdcall QueryInterface(REFIID,void**);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);
        // ISummation specific methods 
        HRESULT __stdcall SumOfTwoIntegers(int,int,int*);
        // ISubtraction specific methods
        HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int*);
        // IMultiplication specific methods
        HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int*);
        // IDivision specific methods
        HRESULT __stdcall DivisionOfTwoIntegers(int,int,int*);
        // Inner Component Initialization Method
        HRESULT __stdcall InitializeInnerComponent(void);
};

class CCalculatorClassFactory: public IClassFactory
{
    private:
        long m_cRef;
    public:
        CCalculatorClassFactory(void);
        ~CCalculatorClassFactory(void);
        
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

// CCalculator Constructor and Destructor

CCalculator::CCalculator(void)
{
    m_pISummation = NULL;
    m_pISubtraction = NULL;
    InterlockedIncrement(&glNumberOfActiveComponents);
}

CCalculator::~CCalculator(void)
{
    InterlockedDecrement(&glNumberOfActiveComponents);
    if(m_pISummation)
    {
        m_pISummation->Release();
        m_pISummation = NULL;
    }
    if(m_pISubtraction)
    {
        m_pISubtraction->Release();
        m_pISubtraction = NULL;
    }
}

// Implementation of CCalculator's IUnknown Specific Methods

HRESULT CCalculator::QueryInterface(REFIID riid, void **ppv)
{
    if(riid==IID_IUnknown)
    {
        *ppv=static_cast<IMultiplication *>(this);
    }
    else if(riid==IID_IMultiplication)
    {
        *ppv=static_cast<IMultiplication *>(this);
    }
    else if(riid==IID_IDivision)
    {
        *ppv=static_cast<IDivision *>(this);
    }
    else if(riid==IID_ISummation)
    {
        *ppv=static_cast<ISummation *>(this);
    }
    else if(riid==IID_ISubtraction)
    {
        *ppv=static_cast<ISubtraction *>(this);
    }
    else
    {
        *ppv=NULL;
        return (E_NOINTERFACE);        
    }
    reinterpret_cast<IUnknown *>(*ppv)->AddRef();
    return (S_OK);
}

ULONG CCalculator::AddRef(void)
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CCalculator::Release(void)
{
    InterlockedDecrement(&m_cRef);
    if(m_cRef == 0)
    {
        delete(this);
        return 0;
    }
    return m_cRef;
}

HRESULT CCalculator::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
    MessageBox(NULL, TEXT("Inside Outer Multiply"), TEXT("Debug"), MB_OK);
    *pMultiplication = num1 * num2;
    return (S_OK);
}

HRESULT CCalculator::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
    *pDivision = num1 / num2;
    return (S_OK);
}

HRESULT CCalculator::SumOfTwoIntegers(int num1, int num2, int *pSummation)
{
    m_pISummation->SumOfTwoIntegers(num1,num2,pSummation);
    return (S_OK);
}

HRESULT CCalculator::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtraction)
{
    m_pISubtraction->SubtractionOfTwoIntegers(num1,num2,pSubtraction);
    return (S_OK);
}

HRESULT CCalculator::InitializeInnerComponent(void)
{
    HRESULT hr;
    hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISummation, (void**)&m_pISummation);
    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("ISummation Interface cannot be found, program will exit now."), TEXT("Error"), MB_OK);
        return(E_FAIL);
    }

    hr = m_pISummation->QueryInterface(IID_ISubtraction, (void**) &m_pISubtraction);
    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("ISubtraction Interface cannot be found, program will exit now."), TEXT("Error"), MB_OK);
        return(E_FAIL);
    }

    return (S_OK);
}


//ClassFactory constructor/destructor/methods start here

CCalculatorClassFactory::CCalculatorClassFactory(void)
{
    m_cRef=1;
}

CCalculatorClassFactory::~CCalculatorClassFactory(void)
{

}


HRESULT CCalculatorClassFactory::QueryInterface(REFIID riid, void **ppv)
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

ULONG CCalculatorClassFactory::AddRef(void)
{
    InterlockedIncrement(&m_cRef);
    return (m_cRef);
}

ULONG CCalculatorClassFactory::Release(void)
{
    InterlockedDecrement(&m_cRef);
    if(m_cRef==0)
    {
        delete(this);
        return (0);
    }
    return (m_cRef); 
}


HRESULT CCalculatorClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
    CCalculator *pCCalculator=NULL;
    HRESULT hr;
    if (pUnkOuter!=NULL)
    {
        return(CLASS_E_NOAGGREGATION);
    }
	pCCalculator = new CCalculator;

    if(pCCalculator == NULL)
    {
        return(E_OUTOFMEMORY);
    }

    hr = pCCalculator->InitializeInnerComponent();
    if (FAILED(hr))
    {
        MessageBox(NULL, TEXT("Inner Component cannot be initialized, program will exit now."), TEXT("Error"), MB_OK);
        pCCalculator->Release();
        return(hr);
    }
    hr = pCCalculator->QueryInterface(riid, ppv);
	pCCalculator->Release();
    return (hr);
}

HRESULT CCalculatorClassFactory::LockServer(BOOL fLock)
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
	CCalculatorClassFactory *pCCalculatorClassFactory=NULL;
    HRESULT hr;
    pCCalculatorClassFactory = new CCalculatorClassFactory;
    if(pCCalculatorClassFactory==NULL)
    {
        return NULL;
    }
    hr = pCCalculatorClassFactory->QueryInterface(riid,ppv);
    pCCalculatorClassFactory->Release();
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


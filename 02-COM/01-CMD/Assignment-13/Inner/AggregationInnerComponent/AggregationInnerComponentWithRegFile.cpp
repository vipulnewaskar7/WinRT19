#include<windows.h>
#include "AggregationInnerComponentWithRegFile.h"

interface INoAggregationIUnknown 
{
    virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**)=0;
    virtual ULONG __stdcall AddRef_NoAggregation(void)=0;
    virtual ULONG __stdcall Release_NoAggregation(void)=0;
};

class CMultiplicationDivision:public INoAggregationIUnknown, IMultiplication, IDivision
{
    private:
        long m_cRef;
        IUnknown *m_pIUnknownOuter;
    public:
        // Constructor of class CMultiplicationDivision
        CMultiplicationDivision(IUnknown*);
        
        // Destructor of class CMultiplicationDivision
        ~CMultiplicationDivision(void);
        
        // Aggregation Supported IUnknown specific method declarations
        HRESULT __stdcall QueryInterface(REFIID, void**);
        ULONG __stdcall AddRef(void);
        ULONG __stdcall Release(void);

        // Aggregation non-supported IUnknown specific method declarations
        HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**);
        ULONG __stdcall AddRef_NoAggregation(void);
        ULONG __stdcall Release_NoAggregation(void);
        
        // IMultiplication Specific method declarations
        HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

        // IDivision Specific method declarations
        HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory:public IClassFactory
{
    private:
    long m_cRef;

    public:
    // Constructor Declaration
    CMultiplicationDivisionClassFactory(void);
    // Destructor Declaration
    ~CMultiplicationDivisionClassFactory();

	HRESULT __stdcall QueryInterface(REFIID, void **);
    ULONG __stdcall AddRef(void);
    ULONG __stdcall Release(void);

    // IClassFactory Specific method declarations
    HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
    HRESULT __stdcall LockServer(BOOL); 
}; 

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;



BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
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




CMultiplicationDivision::CMultiplicationDivision(IUnknown *pIUnknownOuter)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
	if (pIUnknownOuter != NULL)
	{
		m_pIUnknownOuter = pIUnknownOuter;
	}
	else 
	{
		m_pIUnknownOuter = reinterpret_cast<IUnknown*> (static_cast<INoAggregationIUnknown*>(this));
	}
}

CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
		return (m_pIUnknownOuter->QueryInterface(riid, ppv));
}

ULONG CMultiplicationDivision::AddRef(void)
{
	return (m_pIUnknownOuter->AddRef());
}

ULONG CMultiplicationDivision::Release(void)
{
	return (m_pIUnknownOuter->Release());
}



HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
{
	
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<INoAggregationIUnknown *>(this);
	}
	else if (riid == IID_IMultiplication)
	{
		*ppv = static_cast<IMultiplication *>(this);
	}
	else if (riid == IID_IDivision)
	{
		*ppv = static_cast<IDivision *>(this);
	}
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivision::Release_NoAggregation(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return m_cRef;
}

HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	*pMultiplication = num1 * num2;
	return (S_OK);
}

HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	*pDivision = num1 / num2;
	return (S_OK);
}



CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cRef = 1;
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{

}

HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
	{
	
		*ppv = static_cast<IClassFactory *>(this);
	}
	else if (riid == IID_IClassFactory)
	{
	
		*ppv = static_cast<IClassFactory *>(this);
	}
	else
	{
		*ppv = NULL;
	
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *> (*ppv)->AddRef();
	
	return (S_OK);
}

ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return (0);
	}
	return (m_cRef);
}


//
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CMultiplicationDivision *pCMultiplicationDivision = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL && (riid!=IID_IUnknown))
	{
		MessageBox(NULL, TEXT("Inner Component CLASS_E_NOAGGREGATION"), TEXT("Error"), MB_OK);
		return(CLASS_E_NOAGGREGATION);
	}
	pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);

	if (pCMultiplicationDivision == NULL)
	{
		return(E_OUTOFMEMORY);
	}

	hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);
	pCMultiplicationDivision->Release_NoAggregation();
	if (FAILED(hr))
	{
		pCMultiplicationDivision->Release();
		return(hr);
	}
	return (hr);
}


HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return (S_OK);
}


HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision)
	{
		
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	
	if (pCMultiplicationDivisionClassFactory == NULL)
	{
		
		return (E_OUTOFMEMORY);
	}

	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();
	return hr;
}

HRESULT __stdcall DllCanUnloadNow(void)
{
	if (glNumberOfServerLocks == 0 && glNumberOfActiveComponents == 0)
	{
		return (S_OK);
	}
	else
	{
		return (S_FALSE);
	}
}

//---------------------------------------------------------------------------
#include <vcl.h>
#define _WIN32_DCOM
#include <comdef.h>
#include <Wbemidl.h>
#pragma hdrstop

#include "WMIBrightnessEngine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TWMIBrightnessEngine::TWMIBrightnessEngine()
{

	CoInitializeEx(0, COINIT_MULTITHREADED);
	CoInitializeSecurity(
            NULL,
            -1,                          // COM authentication
            NULL,                        // Authentication services
            NULL,                        // Reserved
            RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
            RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
            NULL,                        // Authentication info
            EOAC_NONE,                   // Additional capabilities
            NULL                         // Reserved
			);

}
//---------------------------------------------------------------------------
TWMIBrightnessEngine::~TWMIBrightnessEngine()
{

	CoUninitialize();

}
//---------------------------------------------------------------------------
bool TWMIBrightnessEngine::DecreaseBrightness()
{

	HRESULT hres;

	IWbemLocator *pLoc = NULL;
	IWbemServices *pSvc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *) &pLoc);



	hres = pLoc->ConnectServer(
		WideString(L"ROOT\\WMI").c_bstr(),   // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (for example, Kerberos)
		0,                       // Context object
		&pSvc                    // pointer to IWbemServices proxy
		);

	if (FAILED(hres))
	{

		pLoc->Release();
		return false;                // Program has failed.
	}

	IWbemClassObject* pWmiMonitorBrightness = NULL;
	hres = pSvc->GetObject(L"WmiMonitorBrightness", 0, NULL, &pWmiMonitorBrightness, NULL);

	if (FAILED(hres))
	{

		pSvc->Release();
		pLoc->Release();

		return false;               // Program has failed.
	}

	VARIANT vtProp;

	// Get the value of the Name property
	hres = pWmiMonitorBrightness->Get(L"CurrentBrightness", 0, &vtProp, NULL, NULL);

	IWbemClassObject* pWmiMonitorBrightnessMethods = NULL;
	//hr = pclsObj->PutMethod(); //!!!

	pWmiMonitorBrightness->Release();
	hres = pSvc->GetObject(L"WmiMonitorBrightnessMethods", 0, NULL, &pWmiMonitorBrightnessMethods, NULL);
	IWbemClassObject* pInParamsDefinition = NULL;
	hres = pWmiMonitorBrightnessMethods->GetMethod(L"WmiSetBrightness", 0, &pInParamsDefinition, NULL);

	IWbemClassObject* pClassInstance = NULL;
	hres = pInParamsDefinition->SpawnInstance(0, &pClassInstance);



    // Execute Method
	IWbemClassObject* pOutParams = NULL;
	hres = pSvc->ExecMethod(L"WmiMonitorBrightnessMethods", L"WmiSetBrightness", 0,
		NULL, pClassInstance, &pOutParams, NULL);

	pSvc->Release();
	pLoc->Release();


	return true;

}
//---------------------------------------------------------------------------
void TWMIBrightnessEngine::RestoreBrightness()
{

	//

}
//---------------------------------------------------------------------------

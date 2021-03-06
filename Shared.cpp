//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Shared.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
void GetCurrentMonitorName(HWND hMainForm, String& strName)
{

	HMONITOR hVirtualMonitor = MonitorFromWindow(hMainForm, MONITOR_DEFAULTTONEAREST);
	MONITORINFOEX MIEX = { 0 };
	MIEX.cbSize = sizeof(MONITORINFOEX);
	if (GetMonitorInfo(hVirtualMonitor, &MIEX))
	{

		DISPLAY_DEVICE DD = { 0 };
		DD.cb = sizeof(DD);
		String strResult;
		int i = 0;

		while(EnumDisplayDevices(MIEX.szDevice, i, &DD, 0))
		{

			if (!strResult.IsEmpty())
				strResult += L"\r\n";
			strResult = strResult + DD.DeviceString;
			i++;

		}

		strName = strResult;

		return;
	}

	strName = L"Unknown display device";

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DisplayPowerManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TDisplayPowerManager::TDisplayPowerManager() : m_strDevice("")
{

	memset(&m_PrevDevMode, 0, sizeof(DEVMODE));

}
//---------------------------------------------------------------------------
TDisplayPowerManager::~TDisplayPowerManager()
{

	//

}
//---------------------------------------------------------------------------
bool TDisplayPowerManager::DisableDisplay(HWND hMainForm)
{

	this->EnableDisplay();

	HMONITOR hVirtualMonitor = MonitorFromWindow(hMainForm, MONITOR_DEFAULTTONEAREST);
	MONITORINFOEX MIEX = { 0 };
	MIEX.cbSize = sizeof(MONITORINFOEX);
	if (GetMonitorInfo(hVirtualMonitor, &MIEX))
	{

		DEVMODE CurDevMode;
		memset(&CurDevMode, 0, sizeof(DEVMODE));
		CurDevMode.dmSize = sizeof(DEVMODE);
		if (EnumDisplaySettings(MIEX.szDevice, ENUM_CURRENT_SETTINGS, &CurDevMode))
		{

			m_strDevice = MIEX.szDevice;
			memcpy(&m_PrevDevMode, &CurDevMode, sizeof(DEVMODE));

			CurDevMode.dmPelsWidth = 0;
			CurDevMode.dmPelsHeight = 0;
			//CurDevMode.dmBitsPerPel = 0;
			CurDevMode.dmPosition.x = 0;
			CurDevMode.dmPosition.y = 0;
			//CurDevMode.dmDisplayFrequency = 0;
			//CurDevMode.dmDisplayFlags = 0;
			CurDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_POSITION;
			//CurDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_POSITION |
			//	DM_DISPLAYFREQUENCY | DM_DISPLAYFLAGS;

			LONG lr = ChangeDisplaySettingsEx(MIEX.szDevice, &CurDevMode, NULL, CDS_UPDATEREGISTRY, NULL);

			return true;

		}

	}

	return false;

}
//---------------------------------------------------------------------------
void TDisplayPowerManager::EnableDisplay()
{

	if (/*m_strDevice == "" && */m_PrevDevMode.dmSize)
	{

		m_PrevDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_POSITION;
		LONG lr = ChangeDisplaySettingsEx(m_strDevice.c_str(), &m_PrevDevMode, NULL, CDS_UPDATEREGISTRY, NULL);
		m_strDevice = "";
		memset(&m_PrevDevMode, 0, sizeof(DEVMODE));

    }

}
//---------------------------------------------------------------------------

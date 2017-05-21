//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DXVABrightnessEngine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void errcheck()
{

DWORD dwerr = GetLastError();
	LPTSTR lpMsgBuf = NULL;
	FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
		dwerr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL );


	MessageBox(NULL, lpMsgBuf, TEXT("Error"), MB_OK);

}
//---------------------------------------------------------------------------
TDXVABrightnessEngine::TDXVABrightnessEngine() : m_pPhysicalMonitors(NULL), m_dwMonitorsCount(0),
	m_dwOldBrightness(0)
{

	//

}
//---------------------------------------------------------------------------
TDXVABrightnessEngine::~TDXVABrightnessEngine()
{

	//

}

//---------------------------------------------------------------------------
bool TDXVABrightnessEngine::DecreaseBrightness(HWND hMainForm)
{

	HMONITOR hVirtualMonitor = MonitorFromWindow(hMainForm, MONITOR_DEFAULTTONEAREST);

	if (GetNumberOfPhysicalMonitorsFromHMONITOR(hVirtualMonitor, &m_dwMonitorsCount))
	{

		m_pPhysicalMonitors = new PHYSICAL_MONITOR[m_dwMonitorsCount];
		if (GetPhysicalMonitorsFromHMONITOR(hVirtualMonitor, m_dwMonitorsCount, m_pPhysicalMonitors))
		{

			DWORD dwMonitorCapabilities, dwSupportedColorTemperatures;
			if (GetMonitorCapabilities(m_pPhysicalMonitors[0].hPhysicalMonitor, &dwMonitorCapabilities,
				&dwSupportedColorTemperatures))
			{

				if (dwMonitorCapabilities & MC_CAPS_BRIGHTNESS)
				{

					DWORD dwMinimumBrightness, dwCurrentBrightness, dwMaximumBrightness;

					if (GetMonitorBrightness(m_pPhysicalMonitors[0].hPhysicalMonitor, &dwMinimumBrightness, &dwCurrentBrightness,
						&dwMaximumBrightness)) {

						m_dwOldBrightness = dwCurrentBrightness;

						SetMonitorBrightness(m_pPhysicalMonitors[0].hPhysicalMonitor, dwMinimumBrightness);

						return true;

					}
					else errcheck();

				}

			}
			else errcheck();

		}

	}

	return false;

}
//---------------------------------------------------------------------------
void TDXVABrightnessEngine::RestoreBrightness()
{

	if (!m_pPhysicalMonitors)
		return;

	if (m_dwOldBrightness) {

		SetMonitorBrightness(m_pPhysicalMonitors[0].hPhysicalMonitor, m_dwOldBrightness);

	}

	DestroyPhysicalMonitors(m_dwMonitorsCount, m_pPhysicalMonitors);
	delete[] m_pPhysicalMonitors;

}
//---------------------------------------------------------------------------

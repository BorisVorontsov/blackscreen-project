//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Math.hpp>
#pragma hdrstop

#include "IOCTLBrightnessEngine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TIOCTLBrightnessEngine::TIOCTLBrightnessEngine() : m_hLCDDevice(NULL)
{

	memset(&m_OldDisplayBrightness, 0, sizeof(DISPLAY_BRIGHTNESS));

}
//---------------------------------------------------------------------------
TIOCTLBrightnessEngine::~TIOCTLBrightnessEngine()
{

	//

}
//---------------------------------------------------------------------------
bool TIOCTLBrightnessEngine::DecreaseBrightness(int intThreshold)
{

	DWORD dwBytesReturned = 0;
	HANDLE m_hLCDDevice = CreateFile(L"\\\\.\\LCD", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
		0, NULL);

	if (m_hLCDDevice != INVALID_HANDLE_VALUE)
	{

		if (DeviceIoControl(m_hLCDDevice, IOCTL_VIDEO_QUERY_DISPLAY_BRIGHTNESS, NULL,
			0, (DISPLAY_BRIGHTNESS*)&m_OldDisplayBrightness, sizeof(DISPLAY_BRIGHTNESS), &dwBytesReturned, NULL))
		{

			DISPLAY_BRIGHTNESS DisplayBrightness;
			DisplayBrightness.ucACBrightness = Max(Min(intThreshold, 100), 0);
			DisplayBrightness.ucDCBrightness = Max(Min(intThreshold, 100), 0);
			DisplayBrightness.ucDisplayPolicy = DISPLAYPOLICY_BOTH;

			if (DeviceIoControl(m_hLCDDevice, IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS, (DISPLAY_BRIGHTNESS*)&DisplayBrightness,
				sizeof(DISPLAY_BRIGHTNESS), NULL, 0, &dwBytesReturned, NULL))
			{

				return true;

			}

		}

	}

	return false;

}
//---------------------------------------------------------------------------
void TIOCTLBrightnessEngine::RestoreBrightness()
{

	if (m_hLCDDevice)
	{

		if (!m_OldDisplayBrightness.ucACBrightness && !m_OldDisplayBrightness.ucDCBrightness)
			return;

		DWORD dwBytesReturned = 0;
		DeviceIoControl(m_hLCDDevice, IOCTL_VIDEO_SET_DISPLAY_BRIGHTNESS, (DISPLAY_BRIGHTNESS*)&m_OldDisplayBrightness,
			sizeof(DISPLAY_BRIGHTNESS), NULL, 0, &dwBytesReturned, NULL);

		CloseHandle(m_hLCDDevice);

    }

}
//---------------------------------------------------------------------------

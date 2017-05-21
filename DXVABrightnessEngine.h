//---------------------------------------------------------------------------

#ifndef DXVABrightnessEngineH
#define DXVABrightnessEngineH

#include <PhysicalMonitorEnumerationAPI.h>
#include <HighLevelMonitorConfigurationAPI.h>

class TDXVABrightnessEngine
{
public:
	TDXVABrightnessEngine();
	~TDXVABrightnessEngine();

	bool DecreaseBrightness(HWND hMainForm);
	void RestoreBrightness();

private:
	LPPHYSICAL_MONITOR m_pPhysicalMonitors;
	DWORD m_dwMonitorsCount;
	DWORD m_dwOldBrightness;

};

//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef ApplicationSettingsH
#define ApplicationSettingsH

class TApplicationSettings
{
public:
	TApplicationSettings();
	~TApplicationSettings();

	void ReadSettings();
	void WriteSettings();

	__property bool DecreaseBrightness = { read = m_bDecreaseBrightness };
	__property int BrightnessThreshold = { read = m_intBrightnessThreshold };
	__property bool DisableDisplay = { read = m_bDisableDisplay };

private:
	static const String m_strSettingsFileName;

	bool m_bDecreaseBrightness;
	int m_intBrightnessThreshold;
	bool m_bDisableDisplay;

};
//---------------------------------------------------------------------------
#endif

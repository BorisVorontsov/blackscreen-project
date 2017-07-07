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
	__property int RecentColorIndex = { read = m_intRecentColorIndex, write = m_intRecentColorIndex };

private:
	static const String m_strSettingsFileName;

	bool m_bDecreaseBrightness;
	int m_intBrightnessThreshold;
	int m_intRecentColorIndex;

};
//---------------------------------------------------------------------------
#endif

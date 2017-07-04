//---------------------------------------------------------------------------

#ifndef DisplayPowerManagerH
#define DisplayPowerManagerH

class TDisplayPowerManager
{
public:
	TDisplayPowerManager();
	~TDisplayPowerManager();

	bool DisableDisplay(HWND hMainForm);
	void EnableDisplay();

private:
	String m_strDevice;
	DEVMODE m_PrevDevMode;

};

//---------------------------------------------------------------------------
#endif

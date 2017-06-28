//---------------------------------------------------------------------------

#ifndef DisplayPowerManagerH
#define DisplayPowerManagerH

class TDisplayPowerManager
{
public:
	TDisplayPowerManager();
	~TDisplayPowerManager();

	bool DisableDisplay();
	void EnableDisplay();

private:
	DEVMODE m_PrevDevMode;

};

//---------------------------------------------------------------------------
#endif

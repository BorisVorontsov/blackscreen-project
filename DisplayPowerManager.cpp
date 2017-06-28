//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DisplayPowerManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TDisplayPowerManager::TDisplayPowerManager()
{

	memset(&m_PrevDevMode, 0, sizeof(DEVMODE));

}
//---------------------------------------------------------------------------
TDisplayPowerManager::~TDisplayPowerManager()
{

	//

}
//---------------------------------------------------------------------------
bool TDisplayPowerManager::DisableDisplay()
{

		//SendMessage(Application->Handle, WM_SYSCOMMAND,
		 //	SC_MONITORPOWER, -1);
			//ChangeDisplaySettingsEx

	return true;

}
//---------------------------------------------------------------------------
void TDisplayPowerManager::EnableDisplay()
{

	//

}
//---------------------------------------------------------------------------

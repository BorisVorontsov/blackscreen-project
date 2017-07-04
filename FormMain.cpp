//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
#include "DXVABrightnessEngine.h"
#include "IOCTLBrightnessEngine.h"
#include "DisplayPowerManager.h"
#include "ApplicationSettings.h"
#include "Shared.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMain *Main;

TDXVABrightnessEngine DXVABrightnessEngine;
TIOCTLBrightnessEngine IOCTLBrightnessEngine;
TDisplayPowerManager DisplayPowerManager;

TApplicationSettings ApplicationSettings;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
	: TForm(Owner)
{

	ApplicationSettings.ReadSettings();

}
//---------------------------------------------------------------------------
void __fastcall TMain::FormKeyPress(TObject *Sender, System::WideChar &Key)
{

	if ((this->WindowState == wsMaximized) && (Key == VK_ESCAPE))
		this->ExitFullScreen();

}
//---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject *Sender)
{

	//

}
//---------------------------------------------------------------------------

void __fastcall TMain::FormNCHitTest(TMessage &msg)
{

	if ((this->WindowState == wsNormal) && GetAsyncKeyState(VK_LBUTTON))
		msg.Result = HTCAPTION;
	else
		TForm::Dispatch(static_cast<void*>(&msg));

}

//---------------------------------------------------------------------------
void __fastcall TMain::FormMove(TMessage &msg)
{

	this->LabelMonitorName->Caption = GetCurrentMonitorName(this->Handle);
	TForm::Dispatch(static_cast<void*>(&msg));

}
//---------------------------------------------------------------------------

void __fastcall TMain::BitBtnGoFullScreenClick(TObject *Sender)
{

	if (ApplicationSettings.DecreaseBrightness)
	{

		OSVERSIONINFO OSVI = { 0 };
		OSVI.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&OSVI);

		if (OSVI.dwMajorVersion < 6)
		{

			if (!IOCTLBrightnessEngine.DecreaseBrightness(ApplicationSettings.BrightnessThreshold))
				MessageBeep(MB_ICONEXCLAMATION);

		}
		else
		{

			if (!DXVABrightnessEngine.DecreaseBrightness(this->Handle, ApplicationSettings.BrightnessThreshold))
				MessageBeep(MB_ICONEXCLAMATION);

		}

	}
	else if (ApplicationSettings.DisableDisplay)
	{

		if (!DisplayPowerManager.DisableDisplay(this->Handle))
			MessageBeep(MB_ICONEXCLAMATION);

	}

	this->EnterFullScreen();

}
//---------------------------------------------------------------------------

void __fastcall TMain::BitBtnCloseClick(TObject *Sender)
{

	this->Close();

}
//---------------------------------------------------------------------------
void __fastcall TMain::EnterFullScreen()
{

	LabelMonitorName->Visible = false;
	BitBtnGoFullScreen->Visible = false;
	BitBtnClose->Visible = false;
	this->WindowState = wsMaximized;

}
//---------------------------------------------------------------------------
void __fastcall TMain::ExitFullScreen()
{

	LabelMonitorName->Visible = true;
	BitBtnGoFullScreen->Visible = true;
	BitBtnClose->Visible = true;
	this->WindowState = wsNormal;

	if (ApplicationSettings.DecreaseBrightness)
	{

		DXVABrightnessEngine.RestoreBrightness();
		IOCTLBrightnessEngine.RestoreBrightness();

	}
	else if (ApplicationSettings.DisableDisplay)
	{

		DisplayPowerManager.EnableDisplay();

    }

	while (ShowCursor(TRUE) < 0) {};

}
//---------------------------------------------------------------------------

void __fastcall TMain::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{

	if (this->WindowState == wsMaximized)
	{

		while (ShowCursor(TRUE) < 0) {};

		TimerHideCursor->Enabled = false;
		TimerHideCursor->Enabled = true;

	}

}
//---------------------------------------------------------------------------

void __fastcall TMain::TimerHideCursorTimer(TObject *Sender)
{

	if (this->WindowState == wsMaximized)
	{

		while (ShowCursor(FALSE) >= 0) {};

		TimerHideCursor->Enabled = false;

	}

}
//---------------------------------------------------------------------------

void __fastcall TMain::FormDblClick(TObject *Sender)
{

	if (this->WindowState == wsMaximized)
		this->ExitFullScreen();

}
//---------------------------------------------------------------------------


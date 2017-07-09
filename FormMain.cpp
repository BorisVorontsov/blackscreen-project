//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
#include "DXVABrightnessEngine.h"
#include "IOCTLBrightnessEngine.h"
#include "ApplicationSettings.h"
#include "Shared.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMain *Main;

TDXVABrightnessEngine DXVABrightnessEngine;
TIOCTLBrightnessEngine IOCTLBrightnessEngine;

TApplicationSettings ApplicationSettings;

static TColor BackgroundColors[/*StandardColorsCount*/18] = {
	clBlack,
	clMaroon,
	clGreen,
	clOlive,
	clNavy,
	clPurple,
	clTeal,
	clGray,
	clSilver,
	clRed,
	clLime,
	clYellow,
	clBlue,
	clFuchsia,
	clAqua,
	clLtGray,
	clDkGray,
	clWhite
};

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
	: TForm(Owner)
{

	ApplicationSettings.ReadSettings();

	this->Color = BackgroundColors[ApplicationSettings.RecentColorIndex];

}
//---------------------------------------------------------------------------
void __fastcall TMain::FormKeyPress(TObject *Sender, System::WideChar &Key)
{

	if (this->WindowState == wsMaximized)
	{

		if (Key == VK_ESCAPE)
			this->ExitFullScreen();
		else if (Key == VK_SPACE)
			this->CycleBackground();

	}

}
//---------------------------------------------------------------------------
void __fastcall TMain::FormDestroy(TObject *Sender)
{

	ApplicationSettings.WriteSettings();

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

	String strName;
	GetCurrentMonitorName(this->Handle, strName);
	this->LabelMonitorName->Caption = strName;
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
void __fastcall TMain::CycleBackground()
{

	if ((ApplicationSettings.RecentColorIndex + 1) == static_cast<int>(ARRAYSIZE(BackgroundColors)))
		ApplicationSettings.RecentColorIndex = -1;

	this->Color = BackgroundColors[ApplicationSettings.RecentColorIndex + 1];
	ApplicationSettings.RecentColorIndex = ApplicationSettings.RecentColorIndex + 1;

}
//---------------------------------------------------------------------------


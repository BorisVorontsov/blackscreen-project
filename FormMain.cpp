//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
#include "DXVABrightnessEngine.h"
#include "IOCTLBrightnessEngine.h"
#include "WMIBrightnessEngine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMain *Main;

TDXVABrightnessEngine DXVABrightnessEngine;
TIOCTLBrightnessEngine IOCTLBrightnessEngine;
TWMIBrightnessEngine WMIBrightnessEngine;

//---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner)
	: TForm(Owner)
{
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

	DXVABrightnessEngine.RestoreBrightness();
	IOCTLBrightnessEngine.RestoreBrightness();
	WMIBrightnessEngine.RestoreBrightness();

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

	this->LabelMonitorName->Caption = this->GetCurrentMonitorName();
	TForm::Dispatch(static_cast<void*>(&msg));

}
//---------------------------------------------------------------------------

void __fastcall TMain::BitBtnGoFullScreenClick(TObject *Sender)
{

	OSVERSIONINFO OSVI = { 0 };
	OSVI.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&OSVI);

	if (OSVI.dwMajorVersion < 6)
	{

		if (!IOCTLBrightnessEngine.DecreaseBrightness())
		{

			MessageBeep(MB_ICONEXCLAMATION);

        }

	}
	else
	{

		if (!DXVABrightnessEngine.DecreaseBrightness(this->Handle))
		{

			if (!WMIBrightnessEngine.DecreaseBrightness())
			{

				MessageBeep(MB_ICONEXCLAMATION);

			}

		}

	}

	this->EnterFullScreen();

}
//---------------------------------------------------------------------------
String __fastcall TMain::GetCurrentMonitorName()
{

	HMONITOR hVirtualMonitor = MonitorFromWindow(this->Handle, MONITOR_DEFAULTTONEAREST);
	MONITORINFOEX MIEX = { 0 };
	MIEX.cbSize = sizeof(MONITORINFOEX);
	if (GetMonitorInfo(hVirtualMonitor, &MIEX))
	{

		DISPLAY_DEVICE DD = { 0 };
		DD.cb = sizeof(DD);
		String strResult;
		int i = 0;

		while(EnumDisplayDevices(MIEX.szDevice, i, &DD, 0))
		{

			if (!strResult.IsEmpty())
				strResult += L"\r\n";
			strResult = strResult + DD.DeviceString;
			i++;

		}

		return strResult;
	}

	return L"Unknown display device";

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


//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMain : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *BitBtnGoFullScreen;
	TLabel *LabelMonitorName;
	TBitBtn *BitBtnClose;
	TTimer *TimerHideCursor;
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall BitBtnGoFullScreenClick(TObject *Sender);
	void __fastcall BitBtnCloseClick(TObject *Sender);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall TimerHideCursorTimer(TObject *Sender);
	void __fastcall FormDblClick(TObject *Sender);


private:	// User declarations
	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_NCHITTEST, TMessage, FormNCHitTest)
		VCL_MESSAGE_HANDLER(WM_MOVE, TMessage, FormMove)
	END_MESSAGE_MAP(TForm)

	void __fastcall FormNCHitTest(TMessage &msg);
	void __fastcall FormMove(TMessage &msg);
	void __fastcall EnterFullScreen();
	void __fastcall ExitFullScreen();

public:		// User declarations
	__fastcall TMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
//---------------------------------------------------------------------------
#endif

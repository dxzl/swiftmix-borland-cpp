//---------------------------------------------------------------------------
#ifndef SMListH
#define SMListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>

#include "WMPLib_OCX.h"
#include "WMPLib_TLB.h"
#include "MyCheckLst.hpp"
//---------------------------------------------------------------------------

// Timer times
#define TIME_300  300  // used to sort out what kine of check-box click we got
#define TIME_100  100  // used to delay for start/stop player

// Timer modes
#define TM_NULL                 0
#define TM_START_PLAYER         1
#define TM_STOP_PLAYER          2
#define TM_CHECKBOX_CLICK       3
//---------------------------------------------------------------------------

#define SONG_PATH_SIZE 4096
#define SONG_NAME_SIZE 1024

#define SPI_GETFOCUSBORDERHEIGHT 0x2010 // SystemParametersInfo
#define R2_XORPEN 7 // SetROP2
//---------------------------------------------------------------------------
// Forward class references...
class TImportForm;
class TExportForm;
class TOFMSDlgForm;
//---------------------------------------------------------------------------
struct STRUCT_A
{
  __int32 player;
  __int32 duration;
  __int32 len_path;
  __int32 len_name;
  __int32 len_artist;
  __int32 len_album;

  char path[SONG_PATH_SIZE];
  char name[SONG_NAME_SIZE];
  char artist[SONG_NAME_SIZE];
  char album[SONG_NAME_SIZE];

  __fastcall STRUCT_A(); // constructor
};
//---------------------------------------------------------------------------
struct STRUCT_B
{
  __int32 player;
  __int32 state;

  __fastcall STRUCT_B(); // constructor
};
//---------------------------------------------------------------------------
class TPlaylistForm : public TForm
{
__published:	// IDE-managed Components
  TTimer *Timer1;
  TTimer *FlashTimer;
  TTimer *PositionTimer;
  TPopupMenu *PopupMenu1;
  TMenuItem *ClearList;
  TMenuItem *CheckAll;
  TMenuItem *UncheckAll;
  TMenuItem *DeleteSelected1;
  TPopupMenu *PopupMenu2;
  TMenuItem *EditMode1;
  TMenuItem *N1;
  TMenuItem *ExitEditMode1;
  TMenuItem *N2;
  TMenuItem *MoveSelected;
  TMenuItem *DeleteSelected;
  TMenuItem *RemoveDuplicates1;
  TMenuItem *RandomizeList1;
  TMenuItem *CopySelected;
  TMenuItem *CopySongInfoToClipboard1;
  TMenuItem *SelectAllItems;
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall FlashTimerEvent(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall CheckBoxMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
  void __fastcall CheckBoxClick(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormDeactivate(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall PlayStateChange(WMPPlayState NewState);
  void __fastcall OpenStateChange(WMPOpenState NewState);
  void __fastcall PositionChange(double oldPosition, double newPosition);
  void __fastcall PositionTimerEvent(TObject *Sender);
  void __fastcall CheckBoxClickCheck(TObject *Sender);
  void __fastcall CheckBoxDblClick(TObject *Sender);
  void __fastcall CheckBoxMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall CheckBoxDrawItem(TWinControl *Control, int Index, const TRect &Rect, TOwnerDrawState State);
  void __fastcall CheckBoxMeasureItem(TWinControl *Control, int Index, int &Height);
  void __fastcall CheckBoxDragDrop(TObject *Sender, TObject *Source, int X, int Y);
  void __fastcall CheckBoxDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall ClearListClick(TObject *Sender);
  void __fastcall CheckAllClick(TObject *Sender);
  void __fastcall UncheckAllClick(TObject *Sender);
  void __fastcall DeleteSelected1Click(TObject *Sender);
  void __fastcall EditMode1Click(TObject *Sender);
  void __fastcall ExitEditMode1Click(TObject *Sender);
  void __fastcall MoveSelectedClick(TObject *Sender);
  void __fastcall DeleteSelectedClick(TObject *Sender);
  void __fastcall RemoveDuplicates1Click(TObject *Sender);
  void __fastcall RandomizeList1Click(TObject *Sender);
  void __fastcall CopySelectedClick(TObject *Sender);
  void __fastcall CopySongInfoToClipboard1Click(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall SelectAllItemsClick(TObject *Sender);

private:	// User declarations

  bool __fastcall InsertNewDeleteOld(TMyCheckListBox* SourceList,
                TMyCheckListBox* DestList, int SourceIndex, int &DestIndex );
  void __fastcall SetCheckState(int oldtag);
  void __fastcall QueueToIndex(int Index);
  void __fastcall UpdatePlayerStatus(void);
  bool __fastcall SendToSwiftMix(void * sms, int size, int msg);
  void __fastcall StopPlayer(TWindowsMediaPlayer* p);
  void __fastcall StartPlayer(TWindowsMediaPlayer* p);
  void __fastcall SetTimer(int mode, int time);
  void __fastcall DeleteItem(int ItemIndex);
  void __fastcall CheckAllItems(void);
  void __fastcall DrawFocusRect(TCanvas* c, HPEN hpen, TRect &r);
//  HPEN __fastcall CreateFocusPen();
  void __fastcall WMListDropFile(TWMDropFiles &Msg);
  void __fastcall WMSetText(TWMSetText &Msg);
//  void __fastcall WMMove(TWMMove &Msg);
//  void __fastcall SettingChanged(TMessage &msg);
// to change the the size of the window generated when the
//  void __fastcall UpdateWorkArea(); // the refresh the window and then at the
//  void __fastcall WMWindowPosChanging(TWMWindowPosChanging &msg);

//  HWND snapwin; // the definition of Form2 adsorption where to a handle of the window
//  RECT work_area;
//  bool snapped; // whether the adsorption flag
//  //BOOL would be winprocthing;
//  int thresh; // how far away began to adsorption

  int CheckState, TimerMode;
  bool bInhibitFlash;
  bool bDoubleClick, bCheckClick;
  int Duration, PrevState;
  bool bForceNextPlay, bSkipFilePrompt, bOpening;

  // Properties
  TMyCheckListBox* FCheckBox;
  TPlaylistForm* FOtherForm;
  TWindowsMediaPlayer *FWmp, *FOtherWmp;
  int FNextIndex, FTargetIndex;
  TColor FTextColor;
  bool FInEditMode;
  bool FPlayerA;

  TOFMSDlgForm* pOFMSDlg;
  TExportForm* pExportDlg;
  TImportForm* pImportDlg;

  // Added to intercept a WM_SETTEXT and set unicode window captions
//  Controls::TWndMethod OldWinProc;

protected:

  // property getters
  bool __fastcall GetIsExportDlg(void);
  bool __fastcall GetIsImportDlg(void);
  bool __fastcall GetIsOpenDlg(void);

BEGIN_MESSAGE_MAP
  //add message handler for WM_DROPFILES
  VCL_MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WMListDropFile)
  //add message handler for WM_SETEXT (allows UTF-8 title-bar)
  MESSAGE_HANDLER(WM_SETTEXT, TWMSetText, WMSetText)

  // define the message is called when the window is moved WMWindowPosChanging
//  MESSAGE_HANDLER(WM_WINDOWPOSCHANGING, TWMWindowPosChanging, WMWindowPosChanging);
//  MESSAGE_HANDLER(WM_SETTINGCHANGE, TMessage, SettingChanged);
END_MESSAGE_MAP(TForm)

  // Added to intercept a WM_SETTEXT and set unicode window captions
//  void __fastcall CustomMessageHandler(TMessage &msg);

public:		// User declarations

  bool __fastcall QueueFirst(void);
  void __fastcall NextPlayer(bool bForceStartPlay = false);
  void __fastcall TimeDisplay(int t, int item);
  void __fastcall ClearAndStop(void);
  void __fastcall GetSongInfo(void);
  void __fastcall GetSongInfo(STRUCT_A &sms);
  void __fastcall SetTitleW(void);
  WideString __fastcall GetNext(bool bNoSet = false, bool bEnableRandom = false);
  void __fastcall MySetCaption(WideString wStr);
  void __fastcall MySetCaption(String sStr, bool bStrIsUtf8); // pass in Utf-8
  void __fastcall DestroyImportDialog(void);
  void __fastcall DestroyExportDialog(void);
  void __fastcall DestroyFileDialog(void);
  TImportForm* __fastcall CreateImportDialog(void);
  TExportForm* __fastcall CreateExportDialog(void);
  TOFMSDlgForm* __fastcall CreateFileDialog(void);

  STRUCT_A MediaInfo;

  __property TMyCheckListBox* CheckBox = {read = FCheckBox};
  __property TPlaylistForm* OtherForm = {read = FOtherForm, write = FOtherForm};
  __property TWindowsMediaPlayer* Wmp = {read = FWmp, write = FWmp};
  __property TWindowsMediaPlayer* OtherWmp = {read = FOtherWmp, write = FOtherWmp};
  __property int NextIndex = {read = FNextIndex, write = FNextIndex};
  __property int TargetIndex = {read = FTargetIndex, write = FTargetIndex};
  __property bool PlayerA = {read = FPlayerA, write = FPlayerA};
  __property bool InEditMode = {read = FInEditMode, write = FInEditMode};
  __property bool IsImportDlg = {read = GetIsImportDlg};
  __property bool IsExportDlg = {read = GetIsExportDlg};
  __property bool IsOpenDlg = {read = GetIsOpenDlg};
  __property TColor TextColor = {read = FTextColor};
};
//---------------------------------------------------------------------------
extern PACKAGE TPlaylistForm *ListA;
extern PACKAGE TPlaylistForm *ListB;
//---------------------------------------------------------------------------
#endif

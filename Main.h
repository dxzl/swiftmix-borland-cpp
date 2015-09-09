//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#define VERSION "1.63"
#define FREEWARE_EDITION true
#define DEBUG_ON false // Include a debug console, use MainForm->CWrite("")
//---------------------------------------------------------------------------
// Forward class references...
//class TImportDialog;

#include "DefaultStrings.h"
#include "LicenseKey.h"
#include "WMPLib_OCX.h"
#include "WMPLib_TLB.h"
#include "CWindowDock.h"
#include "XmlTable.h"
#include "RegHelper.h"
#include "Progress.h"
#include "EnterKey.h"
#include "LicenseKey.h"
#include "AutoSize.h"
#include "About.h"
#include "FormSFDlg.h"
#include "FormOFMSDlg.h"
#include "FormDirDlg.h"
#include "FormImportMode.h"
#include "FormExportMode.h"
#include "FormImport.h" // include FormOFDlg.h and SMList.h before this
#include "FormExport.h" // include FormSFDlg.h and SMList.h before this
#include "SMList.h" // include FormOFDlg.h FormImport.h FormExport.h before this

#include <Windows.hpp>

// this has all the exceptions: EFOpenError, EFilerError etc.
// and the TStringlist and TList! It's in Include\vcl
#include <Classes.hpp>
#include <Clipbrd.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <shlobj.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <OleCtrls.hpp>
#include <StdCtrls.hpp>

//---------------------------------------------------------------------------

#define HELPSITE "http://www.yahcolorize.com/SwiftMiX/help/help.htm"
#define WEBSITE "http://www.yahcolorize.com/SwiftMiX/index.htm"
#define EMAIL "dxzl@live.com"
#define REGISTRY_KEY "\\Software\\Discrete-Time Systems\\MusicMixer"

// Registry entries we save in HKEY_CURRENT_USER
#define SM_REGKEY_DIR_A "DefDirA"
#define SM_REGKEY_DIR_B "DefDirB"
#define SM_REGKEY_VOL_A "VolA"
#define SM_REGKEY_VOL_B "VolB"
#define SM_REGKEY_REPEAT_A "RepeatA"
#define SM_REGKEY_REPEAT_B "RepeatB"
#define SM_REGKEY_SHUFFLE_A "ShuffleA"
#define SM_REGKEY_SHUFFLE_B "ShuffleB"
#define SM_REGKEY_FADERTYPE "FaderType"
#define SM_REGKEY_FADERMODE "FaderMode"
#define SM_REGKEY_SENDTIMING "SendTiming"
#define SM_REGKEY_IMPORTEXT "ImportExt"
#define SM_REGKEY_EXPORTEXT "ExportExt"

#define SHGFP_TYPE_CURRENT 0 // current value for user, verify it exists
#define SHGFP_TYPE_DEFAULT 1 // default value, may not exist

#define BIF_NEWDIALOGSTYLE (0x00000040)

#define DISKSPACE_MESSAGEBOX_NONE  0
#define DISKSPACE_MESSAGEBOX_YESNO 1
#define DISKSPACE_MESSAGEBOX_OK    2

#define FIND_FIRST_EX_LARGE_FETCH 2 // increase performance on Win 7 and up...

// Additional FindFirstEx flags
//#define FIND_FIRST_EX_CASE_SENSITIVE 1
//#define FindExInfoStandard 0
//#define FindExInfoBasic 1
//---------------------------------------------------------------------------

#define DVD_SL_MINUS_R_SIZE "4,707,319,808"

// (4.7GB) (4,714,397,696 bytes) (4496MB) DVD
#define DVD_SL_R_12_SIZE "4,700,372,992"

#define DVD_SL_8_SIZE "1,463,386,112"

// (8.5GB) (8,547,991,552 bytes) (8152MB) DVD
#define DVD_DL_12_SIZE "8,543,666,176"

#define CD_74_SIZE "681,984,000"
#define CD_80_SIZE "737,280,000"
#define CD_90_SIZE "829,440,000"
#define CD_99_SIZE "912,384,000"
// (25GB)
#define BLURAY_SL_12_SIZE "25,025,314,816"
// (50GB)
#define BLURAY_DL_12_SIZE "50,050,629,632"
//---------------------------------------------------------------------------

// Standard codes
#define NULLCHAR '\0'
#define TAB '\011'
#define CR '\015' // '\r'
#define LF '\012' // '\n'
#define VT '\013' // Used in RTF text to denote line-breaks (strange!)
#define FF '\014'
#define SPACE '\040'
//---------------------------------------------------------------------------
// Tag value for each WindowsMediaPlayer
#define PLAYER_1 0
#define PLAYER_2 1
//---------------------------------------------------------------------------
// String constants
#define ADD_A_TITLE "Player A"
#define ADD_B_TITLE "Player B"

#define EXPORT_FILE "MyList."
#define EXPORT_EXT "wpl"
#define IMPORT_EXT "wpl"
//---------------------------------------------------------------------------
// Forward class references
class TPlaylistForm;
//---------------------------------------------------------------------------

class TMainForm : public TForm
{
__published:	// IDE-managed Components

  TWindowsMediaPlayer *WindowsMediaPlayer1;
  TTrackBar *TrackBar1;
  TWindowsMediaPlayer *WindowsMediaPlayer2;
  TMainMenu *MainMenu1;
  TMenuItem *Player11;
  TMenuItem *File1;
  TMenuItem *MenuVolumeA;
  TMenuItem *N1;
  TMenuItem *Exit1;
  TMenuItem *VA_25;
  TMenuItem *VA_50;
  TMenuItem *VA_75;
  TMenuItem *VA_100;
  TMenuItem *Player21;
  TMenuItem *File2;
  TMenuItem *MenuVolumeB;
  TMenuItem *VB_25;
  TMenuItem *VB_50;
  TMenuItem *VB_75;
  TMenuItem *VB_100;
  TMenuItem *MenuFaderTypeNormal;
  TMenuItem *N2;
  TMenuItem *MenuAbout;
  TStatusBar *StatusBar1;
  TMenuItem *ClearPlaylistStop1;
  TMenuItem *ClearPlaylistStop2;
  TMenuItem *MenuFaderModeAuto;
  TTimer *AutoFadeTimer;
  TMenuItem *ViewPlaylist1;
  TMenuItem *ViewPlaylist2;
  TMenuItem *MenuHighPriority;
  TMenuItem *N4;
  TMenuItem *MenuForceFade;
  TMenuItem *Player1Next1;
  TMenuItem *Player2Next1;
  TMenuItem *N6;
  TMenuItem *N7;
  TMenuItem *Play1;
  TMenuItem *Stop1;
  TMenuItem *Pause1;
  TMenuItem *N5;
  TMenuItem *N8;
  TMenuItem *Play2;
  TMenuItem *Stop2;
  TMenuItem *Pause2;
  TMenuItem *ImportPlaylist1;
  TMenuItem *ExportPlaylist1;
  TMenuItem *ImportPlaylist2;
  TMenuItem *ExportPlaylist2;
  TMenuItem *MenuHelp;
  TMenuItem *MenuRepeatModeA;
  TMenuItem *N9;
  TMenuItem *MenuRepeatModeB;
  TMenuItem *N10;
  TMenuItem *VA_10;
  TMenuItem *VB_10;
  TMenuItem *N3;
  TMenuItem *MenuExportSongFilesandLists;
  TMenuItem *N11;
  TUpDown *UpDown1;
  TEdit *FadeRate;
  TEdit *FadePoint;
  TUpDown *UpDown2;
  TMenuItem *MenuSendTiming;
  TMenuItem *MenuShuffleModeA;
  TMenuItem *MenuShuffleModeB;
  TMenuItem *MenuViewDiscSpaceRequired;
  TMenuItem *MenuAutoFitToDVDCD;

  void __fastcall File1Click(TObject *Sender);
  void __fastcall File2Click(TObject *Sender);
  void __fastcall VA_25Click(TObject *Sender);
  void __fastcall VA_50Click(TObject *Sender);
  void __fastcall VA_75Click(TObject *Sender);
  void __fastcall VA_100Click(TObject *Sender);
  void __fastcall VB_25Click(TObject *Sender);
  void __fastcall VB_50Click(TObject *Sender);
  void __fastcall VB_75Click(TObject *Sender);
  void __fastcall VB_100Click(TObject *Sender);
  void __fastcall MenuFaderTypeNormalClick(TObject *Sender);
  void __fastcall TrackBar1Change(TObject *Sender);
  void __fastcall Exit1Click(TObject *Sender);
  void __fastcall MenuAboutClick(TObject *Sender);
  void __fastcall ClearPlaylistStop1Click(TObject *Sender);
  void __fastcall ClearPlaylistStop2Click(TObject *Sender);
  void __fastcall MenuFaderModeAutoClick(TObject *Sender);
  void __fastcall AutoFadeTimerEvent(TObject *Sender);
  void __fastcall ViewPlaylist2Click(TObject *Sender);
  void __fastcall ViewPlaylist1Click(TObject *Sender);
  void __fastcall MenuHighPriorityClick(TObject *Sender);
  void __fastcall MenuForceFadeClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall Player1Next1Click(TObject *Sender);
  void __fastcall Player2Next1Click(TObject *Sender);
  void __fastcall Play1Click(TObject *Sender);
  void __fastcall Stop1Click(TObject *Sender);
  void __fastcall Pause1Click(TObject *Sender);
  void __fastcall Play2Click(TObject *Sender);
  void __fastcall Stop2Click(TObject *Sender);
  void __fastcall Pause2Click(TObject *Sender);
  void __fastcall ImportPlaylist1Click(TObject *Sender);
  void __fastcall ExportPlaylist1Click(TObject *Sender);
  void __fastcall ImportPlaylist2Click(TObject *Sender);
  void __fastcall ExportPlaylist2Click(TObject *Sender);
  void __fastcall MenuHelpClick(TObject *Sender);
  void __fastcall MenuRepeatModeAClick(TObject *Sender);
  void __fastcall MenuRepeatModeBClick(TObject *Sender);
  void __fastcall VA_10Click(TObject *Sender);
  void __fastcall VB_10Click(TObject *Sender);
  void __fastcall MenuExportSongFilesandListsClick(TObject *Sender);
  void __fastcall UpDown1Changing(TObject *Sender, bool &AllowChange);
  void __fastcall UpDown2Changing(TObject *Sender, bool &AllowChange);
  void __fastcall WindowsMediaPlayer1OpenStateChange(TObject *Sender, long NewState);
  void __fastcall WindowsMediaPlayer2OpenStateChange(TObject *Sender, long NewState);
  void __fastcall WindowsMediaPlayer1PlayStateChange(TObject *Sender, long NewState);
  void __fastcall WindowsMediaPlayer2PlayStateChange(TObject *Sender, long NewState);
  void __fastcall WindowsMediaPlayer1PositionChange(TObject *Sender, double oldPosition, double newPosition);
  void __fastcall WindowsMediaPlayer2PositionChange(TObject *Sender, double oldPosition, double newPosition);
  void __fastcall MenuSendTimingClick(TObject *Sender);
  void __fastcall MenuShuffleModeAClick(TObject *Sender);
  void __fastcall MenuShuffleModeBClick(TObject *Sender);
  void __fastcall WindowsMediaPlayer1MediaChange(TObject *Sender, LPDISPATCH Item);
  void __fastcall WindowsMediaPlayer2MediaChange(TObject *Sender, LPDISPATCH Item);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall MenuViewDiscSpaceRequiredClick(TObject *Sender);
  void __fastcall MenuAutoFitToDVDCDClick(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall WindowsMediaPlayerError(TObject *Sender);

private:	// User declarations
#if DEBUG_ON
  void __fastcall CInit(void);
#endif
  void __fastcall CopyMusicFiles(TPlaylistForm* f, WideString wUserDir);
  bool __fastcall PromptAbort(WideString s);
  WideString __fastcall DirectoryDialogW(WideString sInitialDir, WideString sTitle);
  bool __fastcall IsWinVistaOrHigher(void);
  void __fastcall ErrorCode(int Code);
  void __fastcall AddAllSongsToListBox(TPlaylistForm* f);
  void __fastcall RecurseFileAdd(TStringList* slFiles);
  void __fastcall AddFilesToStringList(TStringList* slFiles);
  bool __fastcall IsAudioFile(String sFile);
  bool __fastcall SetVolumes(void);
  void __fastcall SetVolumeCheckmarksA(int v);
  void __fastcall SetVolumeCheckmarksB(int v);
  __int64 __fastcall ComputeDiskSpace(int Mode);
  unsigned __int64 __fastcall RandomRemove(unsigned __int64 TargetBytes);
  void __fastcall WMDropFile(TWMDropFiles &Msg);

  int volA, volB;

  int m_filesAddedCount;

  // Flags for registry settings
  bool bTypeCenterFade, bModeManualFade, bSendTiming;
  bool bRepeatModeA, bShuffleModeA;
  bool bRepeatModeB, bShuffleModeB;

  // Globals for Trial-Version
  bool bTrialFeaturesEnabled;
  int CurrentPlayer;

  WideString DeskDir;

  TPlaylistForm* GPlaylistForm;

  // properties
  WideString FwDeskDir;
  String FsImportExt, FsExportExt; // Import/Export file-extension (UTF-8)
  String FsSaveDirA, FsSaveDirB; // open/save directory (UTF-8)

  bool FBypassFilters;

//  CWindowDock* FDock;

protected:

  String __fastcall GetDeskDir(void);

//  void __fastcall WndProc(TMessage &Message);

BEGIN_MESSAGE_MAP
  //add message handler for WM_DROPFILES
  // NOTE: All of the TWM* types are in messages.hpp!
  VCL_MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WMDropFile)
//  VCL_MESSAGE_HANDLER(WM_NOTIFY, TOFNotify, WMOFNotify)
  //add message handler for WM_MOVE
//  VCL_MESSAGE_HANDLER(WM_MOVE, TWMMove, WMMove)
END_MESSAGE_MAP(TForm)

public:		// User declarations

  __fastcall TMainForm(TComponent* Owner);

#if DEBUG_ON
  void __fastcall CWrite(String S);
#endif

  void __fastcall ShowPlaylist(TPlaylistForm* f);
  String __fastcall SetFlag(String S, int f);
  String __fastcall PercentEncode(String sIn, const char* table, bool bEncodeAbove127);
  bool __fastcall ForceFade(void);
  bool __fastcall SetCurrentPlayer(void);
  void __fastcall RestoreFocus(void);
  bool __fastcall FileDialog(TPlaylistForm* f, String &d, String t);
  void __fastcall LoadListWithDroppedFiles(TWMDropFiles &Msg, TPlaylistForm* f);
  bool __fastcall AddFileToListBox(TPlaylistForm* f, String sFile, bool bConvertToUtf8);

  // Utils
  String __fastcall Utf8ToAnsi(String sIn);
  String __fastcall AnsiToUtf8(String sIn);
  String __fastcall WideToUtf8(WideString sIn);
  WideString __fastcall Utf8ToWide(String sIn);
  String __fastcall ReplaceAll(String sIn, char c1, char c2);
  String __fastcall ReplaceAll(String sIn, String S1, String S2);
  WideString __fastcall ReplaceAllW(WideString sIn, WideString S1, WideString S2);
  WideString __fastcall ReplaceAllW(String sIn, wchar_t c1, wchar_t c2);
  bool __fastcall SetCurrentDirW(WideString wDir);
  WideString __fastcall GetCurrentDirW(void);
  WideString __fastcall ExtractFileExtW(WideString sIn);
  void __fastcall ShowMessageW(WideString wStr);
  void __fastcall ShowMessageU(String uStr);
  bool __fastcall DirectoryExistsW(WideString wPath);
  bool __fastcall FileExistsW(WideString wPath);
  String __fastcall ReadStringFromFileW(WideString wPath);
  bool __fastcall WriteStringToFileW(WideString wPath, String sInfo);
  WideString __fastcall GetSpecialFolder(int csidl);

  int FadeAt;
  bool bFadeRight;

  int RWM_SwiftMixPlay;
  int RWM_SwiftMixTime;
  int RWM_SwiftMixState;

  bool bAutoSizePrompt;

  // properties
  __property String ImportExt = {read = FsImportExt, write = FsImportExt};
  __property String ExportExt = {read = FsExportExt, write = FsExportExt};
  __property String SaveDirA = {read = FsSaveDirA, write = FsSaveDirA};
  __property String SaveDirB = {read = FsSaveDirB, write = FsSaveDirB};
  __property String DeskDirUtf8 = {read = GetDeskDir};
  __property bool GBypassFilters = {read = FBypassFilters, write = FBypassFilters, default =  false};
  __property bool ManualFade = {read = bModeManualFade};
  __property bool CenterFade = {read = bTypeCenterFade};
  __property bool SendTiming = {read = bSendTiming};
  __property bool RepeatModeA = {read = bRepeatModeA};
  __property bool RepeatModeB = {read = bRepeatModeB};
  __property bool ShuffleModeA = {read = bShuffleModeA};
  __property bool ShuffleModeB = {read = bShuffleModeB};
  __property int VolA = {read = volA};
  __property int VolB = {read = volB};
  __property int FilesAddedCount = {read = m_filesAddedCount, write = m_filesAddedCount};
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
extern const char Trial_Key[];

typedef HRESULT __stdcall (*tGetFolderPath)(HWND hwndOwner, int nFolder, HANDLE hToken, DWORD dwFlags, LPTSTR pszPath);
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
#ifndef FormExportH
#define FormExportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
// Forward class references...
class TSFDlgForm;
class TExportModeForm;
class TPlaylistForm;
//---------------------------------------------------------------------------

class TExportForm : public TForm
{
__published:	// IDE-managed Components
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations
  String __fastcall PercentEncode(String sIn, const WideChar* table, bool bEncodeAbove127);
  String __fastcall InsertXMLSpecialCodes(String sIn);
  String __fastcall XmlSpecialCharEncode(WideChar c);
  String __fastcall GetFileString(String uListFullPath,
                                      String sSongFullPath, int Mode);
  String __fastcall StripFileUriPrefixIfAny(String &sIn);
  String __fastcall UniversalExtractFileName(String sIn);
  bool __fastcall IsUri(String sIn);
  String __fastcall ProcessFileName(String &uName, String uListFullPath,
                            int Mode, bool bUncPathFormat);

  TSFDlgForm* pSFDlg;
  TExportModeForm* pExpModeDlg;

public:		// User declarations
  __fastcall TExportForm(TComponent* Owner);
  __fastcall ~TExportForm();

  int __fastcall Dialog(TPlaylistForm* f, String d, String t);
  int __fastcall NoDialog(TPlaylistForm* f, String uListFullPath, int Mode,
                               int Enc, bool bUncPathFormat, bool bWriteBOM);
};
//---------------------------------------------------------------------------
extern PACKAGE TExportForm *ExportForm;
//---------------------------------------------------------------------------
#endif

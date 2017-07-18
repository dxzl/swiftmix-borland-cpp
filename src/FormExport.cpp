//---------------------------------------------------------------------------
#include <vcl.h>
#include "Main.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TExportForm *ExportForm;
//---------------------------------------------------------------------------
// See also: _wsplitpath, _wfnsplit, _wfnmerge, _wchdir, _wgetcwd, _wgetcurdir, _wmakepath, _wfullpath
//---------------------------------------------------------------------------
__fastcall TExportForm::TExportForm(TComponent* Owner)
  : TForm(Owner)
{
  pSFDlg = NULL;
  pExpModeDlg = NULL;
}
//---------------------------------------------------------------------------
__fastcall TExportForm::~TExportForm()
{
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::FormCreate(TObject *Sender)
{
  Application->CreateForm(__classid(TSFDlgForm), &pSFDlg);
  Application->CreateForm(__classid(TExportModeForm), &pExpModeDlg);
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::FormDestroy(TObject *Sender)
{
#if DEBUG_ON
  MainForm->CWrite( "\r\nFormDestroy() in TExportForm()!\r\n");
#endif
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  if (pSFDlg != NULL)
    pSFDlg->Release();

  if (pExpModeDlg != NULL)
    pExpModeDlg->Release();

#if DEBUG_ON
  MainForm->CWrite( "\r\nFormClose() in TExportForm()!\r\n");
#endif
}
//---------------------------------------------------------------------------
int __fastcall TExportForm::Dialog(TPlaylistForm* f, String d, String t)
// Title (t) and Initial directory (d) are UTF-8
{
#if (FREEWARE_EDITION == false)
  if (PK->ComputeDaysRemaining() <= 0)
  {
    ShowMessage("Trial Expired, visit:\n" + String(WEBSITE));
    return -1;
  }
#endif

  if (f == NULL || pExpModeDlg == NULL || pSFDlg == NULL)
    return 0;

  if (f->Count == 0 || f->PlayTag < 0)
    return 0;

  int Count = -1;

  try
  {
    pSFDlg->Filters = String("All Files (*.*)|*.*|"
                  "Windows Media (wpl)|*.wpl|"
                  "MPEG UTF-8 (m3u8)|*.m3u8|"
                  "MPEG ANSI (m3u)|*.m3u|"
                  "Adv Stream XML (asx)|*.asx|"
                  "XML Shareable (xspf)|*.xspf|"
                  "Win Audio XML (wax)|*.wax|"
                  "Windows XML (wmx)|*.wmx|"
                  "Winamp (pls)|*.pls|"
                  "Text (txt)|*.txt");

    // Run the TSaveDialog and get a file name...
    String uDefFile = String(EXPORT_FILE) + String(EXPORT_EXT);

    if (pSFDlg->Execute(uDefFile, d, t) == FALSE)
      return -1; // -1 will suppress an error-message

    String uName = pSFDlg->FileName; // Get UTF-8 filepath

    if (uName.IsEmpty())
      return -1;

    String sPlayer = f == ListA ? "A" : "B";
    pExpModeDlg->Title = "Export Player " + sPlayer + " List";
    pExpModeDlg->FileName = uName;
    pExpModeDlg->Mode = EXPORT_PATH_ABSOLUTE;

    if (pExpModeDlg->ShowModal() == mrCancel)
      return -1;

    String wName = pSFDlg->FileName;
    bool bFileExists = FileExists(wName);

    if (bFileExists)
    {
      String sMsg = String("File Already Exists:\n\n\"") +  wName +
                                            String("\"\n\nOverwrite it?");

      int button = MessageBox(MainForm->Handle, sMsg.w_str(),
              L"File Exists", MB_YESNO + MB_ICONQUESTION + MB_DEFBUTTON1);

      if (button == IDNO)
        return -1; // Don't print error message
    }

    // Gets the count of items exported
    Count = NoDialog(f, wName, pExpModeDlg->Mode, pExpModeDlg->Encoding,
                    pExpModeDlg->UncPathFmt, pExpModeDlg->WriteBOM);
  }
  catch(...) {}

  return Count;
}
//---------------------------------------------------------------------------
int __fastcall TExportForm::NoDialog(TPlaylistForm* f, String uListFullPath,
                  int Mode, int Enc, bool bUncPathFormat, bool bWriteBOM)
//
// uListFullPath must be UTF-8 (we use MainForm->WriteStringToFileW() to save the UTF-8 TStringList()...
// (we use the vcl's ansi string-parsing functions on uListFullPath - they work on a utf-8 string
// but not on a WideString)
//
// The bSaveAsAnsi and bUncPathFormat flags pertain to the file-paths in the play-list
//
// Mode
// EXPORT_PATH_RELATIVE       0
// EXPORT_PATH_ROOTED         1
// EXPORT_PATH_ABSOLUTE       2
// EXPORT_PATH_NONE           3
{
  if (f == NULL)
    return 0;

  if (f->Count == 0 || f->PlayTag < 0)
    return 0;

  int Count = 0;

  TStringList* sl = new TStringList();

  if (sl == NULL)
    return 0;

  try
  {
    int len = f->Count;

    String Ext = ExtractFileExt(uListFullPath).LowerCase();

    if (Ext.Length() > 0 && Ext.Pos(".") == 1)
      Ext.Delete(1, 1);

    MainForm->ExportExt = Ext; // Save as UTF-8

    String sTemp, sSavePrefix;

    TProgressForm::Init(len);

    String sEnc;
    if (Enc == EXPORT_MODE_ANSI)
      sEnc = "\"ANSI\"";
    else if (Enc == EXPORT_MODE_UTF16BE)
      sEnc ="\"UTF-16BE\"";
    else if (Enc == EXPORT_MODE_UTF16)
      sEnc ="\"UTF-16\"";
    else
      sEnc ="\"UTF-8\"";

    if (Ext == "wpl")
    {
      sl->Add("<?wpl version=\"1.0\"?>");
      sl->Add("<smil>");
      sl->Add(" <head>");
      // From a file generated by Windows Media Player:
      // <meta name="Generator" content="Microsoft Windows Media Player -- 12.0.9600.17415"/>
      // <meta name="ItemCount" content="85"/>
      sl->Add("   <meta name=\"Generator\" content=\"SwiftMiX Player -- " + String(VERSION) + "\"/>");
      sl->Add("   <title>" + ExtractFileName(uListFullPath) + "</title>");
      sl->Add(" </head>");
      sl->Add(" <body>");
      sl->Add("   <seq>");

      for (int ii = 0; ii < len; ii++)
      {
        try
        {
          String sName = f->GetString(ii);

          if (sName.IsEmpty()) continue;

          // tack on a leading "file://", ProcessFileName will strip it off then add it back...
          if (bUncPathFormat && !MainForm->IsUri(sName))
              sName = sName.Insert("file://", 1);

          // Note: sName is returned as a ref with the song-title (filename)
          sTemp = ProcessFileName(sName, uListFullPath, Mode, bUncPathFormat);

          if (!sTemp.IsEmpty())
          {
            sTemp = InsertXMLSpecialCodes(sTemp); // replace "&" with "&amp;"

            sl->Add("     <media src=\"" + sTemp + "\"/>");
            Count++;
          }
        }
        catch(...) { }

        TProgressForm::Move(ii);
      }
      sl->Add("   </seq>");
      sl->Add(" </body>");
      sl->Add("</smil>");
    }
    else if (Ext == "xspf") // Save as Windows-Media-Player XML file
    {
      sl->Add("<?xml version=\"1.0\" encoding=" + sEnc + "?>");
      sl->Add("<playlist version=\"1\" xmlns=\"http://xspf.org/ns/0/\">");
      sl->Add(" <tracklist>");

      for (int ii = 0 ; ii < len ; ii++)
      {
        try
        {
          String sName = f->GetString(ii);

          if (sName.IsEmpty()) continue;

          // tack on a leading "file://", ProcessFileName will strip it off then add it back...
          if (bUncPathFormat && !MainForm->IsUri(sName))
            sName = sName.Insert("file://", 1);

          // Note: sName is returned as a ref with the song-title (filename)
          sTemp = ProcessFileName(sName, uListFullPath, Mode, bUncPathFormat);

          if (!sTemp.IsEmpty())
          {
            if (bUncPathFormat)
              sTemp = PercentEncode(sTemp, PERCENTCHARS, true); // also encode chars above 127
            else
              sTemp = InsertXMLSpecialCodes(sTemp); // replace "&" with "&amp;"

            sl->Add("   <track>");
            sl->Add("     <title>" + sName + "</title>");
            sl->Add("     <location>" + sTemp + "</location>");
            sl->Add("   </track>");
            Count++;
          }
        }
        catch(...) { }

        TProgressForm::Move(ii);
      }

      sl->Add(" </tracklist>");
      sl->Add("</playlist>");
    }
    else if (Ext == "asx" || Ext == "wax" || Ext == "wmx") // Save as Windows-Media-Player XML file
    {
      sl->Add("<ASX version = \"3.0\">");
      sl->Add("   <PARAM name = \"encoding\" value = " + sEnc + " />");
      sl->Add("   <TITLE>" + ExtractFileName(uListFullPath) + "</TITLE>");

      for (int ii = 0 ; ii < len ; ii++)
      {
        try
        {
          String sName = f->GetString(ii);

          if (sName.IsEmpty()) continue;

          // tack on a leading "file://", ProcessFileName will strip it off then add it back...
          if (bUncPathFormat && !MainForm->IsUri(sName))
              sName = sName.Insert("file://", 1);

          // sName is returned by reference with the Title (filename)
          sTemp = ProcessFileName(sName, uListFullPath, Mode, bUncPathFormat);

          if (!sTemp.IsEmpty())
          {
            sl->Add("   <ENTRY>");
            sl->Add("     <TITLE>" + sName + "</TITLE>");
            sl->Add("     <REF HREF = \"" + sTemp + "\" />");
            sl->Add("   </ENTRY>");
            Count++;
          }
        }
        catch(...) { }

        TProgressForm::Move(ii);
      }

      sl->Add("</ASX>");
    }
    else if (Ext == "pls") // Save as PLSv2 (Winamp)
    {
      sl->Add("[playlist]");

      for (int ii = 0 ; ii < len ; ii++)
      {
        try
        {
          String sName = f->GetString(ii);

          if (sName.IsEmpty()) continue;

          // tack on a leading "file://", ProcessFileName will strip it off then add it back...
          if (bUncPathFormat && !MainForm->IsUri(sName))
              sName = sName.Insert("file://", 1);

          // Note: sName is returned as a ref with the song-title (filename)
          sTemp = ProcessFileName(sName, uListFullPath, Mode, bUncPathFormat);

          if (!sTemp.IsEmpty())
          {
            if (bUncPathFormat)
              sTemp = PercentEncode(sTemp, PERCENTCHARS, true); // also encode chars above 127

            String sCount = String(Count+1) + "=";
            sl->Add("File" + sCount + sTemp);
            sl->Add("Title" + sCount + UniversalExtractFileName(sTemp));
            sl->Add("Length" + sCount + "-1"); // ignore length (usually for streaming)
            Count++;
          }
        }
        catch(...) { }

        TProgressForm::Move(ii);
      }

      sl->Add("NumberOfEntries=" + String(Count));
      sl->Add("Version=2");
    }
    else // handle m3u and m3u8
    {
      // Save as plain-text file
      for (int ii = 0 ; ii < len ; ii++)
      {
        try
        {
          String sName = f->GetString(ii);

          if (sName.IsEmpty()) continue;

          // tack on a leading "file://", ProcessFileName will strip it off then add it back...
          if (bUncPathFormat && !MainForm->IsUri(sName))
              sName = sName.Insert("file://", 1);

          // Note: sName is returned as a ref with the song-title (filename)
          sTemp = ProcessFileName(sName, uListFullPath, Mode, bUncPathFormat);

          if (!sTemp.IsEmpty())
          {
            if (bUncPathFormat)
              sTemp = PercentEncode(sTemp, PERCENTCHARS, true); // also encode chars above 127

            sl->Add(sTemp);
            Count++;
          }
        }
        catch(...) { }

        TProgressForm::Move(ii);
      }
    }

    if (sl->Count > 0)
    {
      sl->WriteBOM = bWriteBOM;

      TEncoding* enc;
      if (Enc == EXPORT_MODE_ANSI)
        enc = TEncoding::ANSI;
      else if (Enc == EXPORT_MODE_UTF8)
        enc = TEncoding::UTF8;
      else if (Enc == EXPORT_MODE_UTF16)
        enc = TEncoding::Unicode;
      else if (Enc == EXPORT_MODE_UTF16BE)
        enc = TEncoding::BigEndianUnicode;

      sl->SaveToFile(uListFullPath, enc);
    }

    TProgressForm::UnInit();
  }
  catch(...) { ShowMessage("Error In NoDialog()"); }

  delete sl;
  return Count;
}
//---------------------------------------------------------------------------
String __fastcall TExportForm::ProcessFileName(String &uName,
        String uListFullPath, int Mode, bool bUncPathFormat)
// uName is the full utf-8 file path from the list-box. It can be in
// "file:/localhost/drive/path/file.ext" format
// or like "C:\path\song.wma", "relative-path\song.wma",
// "\rooted-relative-path\song.wma"
// ".\path\song.wma", "..\path\song.wma", "./path/song.mp3"
// uName contains the File name only on return
// We return the path we want to write into to the playlist
{
  try
  {
    String sTemp = uName;

    // Return the title (filename) in uName
    uName = UniversalExtractFileName(sTemp);

    // If it's a non-file URL like HTTP://, just return it as-is...
    if (MainForm->IsUri(sTemp) && !MainForm->IsFileUri(sTemp))
      return sTemp;

    // Convert to "normal" file-path we can work with
    String sSavePrefix = StripFileUriPrefixIfAny(sTemp);

    // Ok, it's a file: URI. Convert to normal Windows path if needed and apply user path options...
    sTemp = GetFileString(uListFullPath, sTemp, Mode); // add user-selected path options

    if (bUncPathFormat)
    {
      sTemp = ReplaceStr(sTemp, "\\", "/");

      // FYI: Looks like Microsoft metafiles that have relative links HAVE to
      // be on the local server... then you access those playlists via an ASX
      // metafile at the client which has a <ENTRYREF HREF = "" />
      // that points to the remote playlist...
      if (Mode != EXPORT_PATH_RELATIVE)
        sTemp = sTemp.Insert(sSavePrefix, 1); // put back the "file:/localhost/" part...
      else if (sTemp.Pos("./") != 1) // don't keep adding more!
        sTemp = sTemp.Insert("./", 1); // this is required for UNIX paths (ok for Windows too!)
    }

    return sTemp;
  }
  catch(...)
  {
    ShowMessage("Error In ProcessFileName()");
    return "";
  }
}
//---------------------------------------------------------------------------
String __fastcall TExportForm::GetFileString(String uListFullPath,
                                            String sSongFullPath, int Mode)
// uListFullPath is the path/filename of the list we are writing to.
// sSongFullPath is the path/filename of the song.
//
// Mode:
// EXPORT_PATH_RELATIVE       0
// EXPORT_PATH_ROOTED         1
// EXPORT_PATH_ABSOLUTE       2
// EXPORT_PATH_NONE           3
//
// Only call this with a path of the form "file:/localhost/drive/path/file.ext"
//
// This function converts the input path to a "standard" file path and applies
// the user's chosen Mode to it. The return string is a "standard" path without
// the "file:" prefix and with "/" changed to "\"
//
{
  // ANSI ReplaceAll should work ok on a UTF-8 path...
  sSongFullPath = ReplaceStr(sSongFullPath, "/", "\\");

  try
  {
    String sTemp; // default returned string...

    if (Mode == EXPORT_PATH_RELATIVE)
    {
      // This function returns FileNameAndPath if the song is on a different
      // drive than the list's RootPath
      // The relative path returned has no leading backslash. "..\..\" are
      // inserted automatically to go up.
      try { sTemp = ExtractRelativePath(ExtractFilePath(uListFullPath), sSongFullPath); }
      catch(...) { ShowMessage("Error 1 In GetFileString()"); }
    }
    else if (Mode == EXPORT_PATH_NONE)
      sTemp = ExtractFileName(sSongFullPath);
    else if (Mode == EXPORT_PATH_ROOTED)
    {
      String sDrive = ExtractFileDrive(sSongFullPath);

      if (!sDrive.IsEmpty())
      {
        int pos = uListFullPath.Pos(sDrive);
        if (pos > 0)
        {
          TReplaceFlags rFlags = (TReplaceFlags() << rfIgnoreCase); // set StringReplace behavior
          sTemp = StringReplace(sSongFullPath, sDrive, "", rFlags); // strip drive
        }
      }
    }
    else // EXPORT_PATH_ABSOLUTE
      sTemp = sSongFullPath;

    return sTemp;
  }
  catch(...) { ShowMessage("Error 2 In GetFileString()"); return ""; }
}
//---------------------------------------------------------------------------
String __fastcall TExportForm::InsertXMLSpecialCodes(String sIn)
{
  String sOut;

  // Special XML replacements...
  try
  {
    int len = sIn.Length();
    for(int ii = 1 ; ii <= len; ii++)
      sOut += XmlSpecialCharEncode(sIn[ii]);
  }
  catch(...) { }

  return sOut;
}
//---------------------------------------------------------------------------
String __fastcall TExportForm::XmlSpecialCharEncode(WideChar c)
{
  for (int ii = 0; ii < XMLCODESLEN; ii++)
    if (XMLCHARS[ii] == c)
      return XMLCODES[ii];

  return c;
}
//---------------------------------------------------------------------------
String __fastcall TExportForm::StripFileUriPrefixIfAny(String &sIn)
// Returns sIn by reference "as-is" or with the "file:/localhost/" part stripped.
// The "normal" return string is empty if no changes were made to sIn or
// it contains the "file:/localhost/" part so it can be restored if needed...
{
  try
  {
    if (sIn.Length() < 8) return "";
    String sTemp = sIn.SubString(1, 6).LowerCase();
    if (sTemp != "file:/") return "";
    int len = sIn.Length();
    int ii = 7; // start looking for the next / after file:/
    for (; ii <= len; ii++)
      if (sIn[ii] == '/') break;

    // S.S. Changed 7/22/16 (1-based indices for these strings!)
//    if (ii == len) return ""; // did not find second '/'!
    if (ii > len) return ""; // did not find second '/'!

    sTemp = sIn.SubString(1, ii);
    sIn = sIn.SubString(ii+1, len-(ii+1)+1);
    return sTemp;
  }
  catch(...) { return ""; }
}
//---------------------------------------------------------------------------
String __fastcall TExportForm::UniversalExtractFileName(String sIn)
{
  int len = sIn.Length();
  int idx = len;
  WideChar c;

  for(;;)
  {
    if (idx == 0) break;
    c = sIn[idx];
    if (c == '\\' || c == '/') break;
    idx--;
  }

  if (idx != 0)
    return sIn.SubString(idx+1, len-(idx+1)+1);

  return sIn;
}
//---------------------------------------------------------------------------
String __fastcall TExportForm::PercentEncode(String sIn,
                                const WideChar* table, bool bEncodeAbove127)
{
  String sOut;
  int len = sIn.Length();
  int lenPercent = StrLen(table);
  for (int ii = 1; ii <= len; ii++)
  {
    WideChar c = sIn[ii];
    int jj;
    for (jj = 0; jj < lenPercent; jj++)
    {
      if (c == table[jj])
      {
        // hex encode SPACE, etc.
        sOut += "%" + IntToHex((int)(WideChar)c, 2);
        break;
      }
    }

    // if not found in the special chars table, handle it below...
    if (jj >= lenPercent)
    {
      // hex encode the control chars
      if ((WideChar)c < SPACE) sOut += "%" + IntToHex((int)(WideChar)c, 2);
      else if (bEncodeAbove127 && (WideChar)c > 127) sOut += "%" + IntToHex((int)(WideChar)c, 2);
      else sOut += c;
    }
  }
  return sOut;
}
//---------------------------------------------------------------------------

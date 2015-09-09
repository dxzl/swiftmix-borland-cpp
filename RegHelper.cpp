//---------------------------------------------------------------------------
#pragma package(smart_init)
#include "Main.h"
#pragma hdrstop

#include "RegHelper.h"

//---------------------------------------------------------------------------
//  constructor
__fastcall TRegHelper::TRegHelper(bool bCreate)
{
  Reg = new TRegistry();

  if (Reg == NULL)
  {
#if DEBUG_ON
    MainForm->CWrite( "\r\nUnable to create TRegistry()!\r\n");
#endif
    bOpened = false;
    return;
  }

  if (!Reg->OpenKey(REGISTRY_KEY, bCreate))
  {
#if DEBUG_ON
    MainForm->CWrite( "\r\nUnable to open Registry()!\r\n");
#endif
    bOpened = false;
    return;
  }

  bOpened = true;
}
//------------------- destructor -------------------------
__fastcall TRegHelper::~TRegHelper()
{
  try
  {
    if (Reg != NULL)
    {
      if (bOpened)
        Reg->CloseKey();

      delete Reg;
    }
  }
  catch(...) {}
}
//---------------------------------------------------------------------------
WideString __fastcall TRegHelper::ReadSetting(String keyName)
{
  WideString sOut;

  // Read key from registry at HKEY_CURRENT_USER
  if (!bOpened)
    return "";

  try
  {
    String s = Reg->ReadString(keyName);
    sOut = MainForm->Utf8ToWide(s);
  }
  catch (...)
  {
    sOut = "";
  }

  return sOut;
}
//---------------------------------------------------------------------------
void __fastcall TRegHelper::ReadSetting(String keyName, bool &bVal, bool bDef)
{
  // Read key from registry at HKEY_CURRENT_USER
  if (!bOpened)
    return;

  try
  {
    bVal = Reg->ReadBool(keyName);
  }
  catch(...)
  {
    bVal = bDef;
  }
}
//---------------------------------------------------------------------------
void __fastcall TRegHelper::ReadSetting(String keyName, int &iVal, int iDef)
{
  // Read key from registry at HKEY_CURRENT_USER
  if (!bOpened)
    return;

  try
  {
    iVal = Reg->ReadInteger(keyName);
  }
  catch(...)
  {
    iVal = iDef;
  }
}
//---------------------------------------------------------------------------
void __fastcall TRegHelper::WriteSetting(String keyName, WideString sIn)
{
  // Read key from registry at HKEY_CURRENT_USER
  if (!bOpened)
    return;

  try
  {
    Reg->WriteString(keyName, MainForm->WideToUtf8(sIn));
  }
  catch(...) {}
}
//---------------------------------------------------------------------------
void __fastcall TRegHelper::WriteSetting(String keyName, bool bVal)
{
  // Read key from registry at HKEY_CURRENT_USER
  if (!bOpened)
    return;

  try
  {
    Reg->WriteBool(keyName, bVal);
  }
  catch(...) {}
}
//---------------------------------------------------------------------------
void __fastcall TRegHelper::WriteSetting(String keyName, int iVal)
{
  // Read key from registry at HKEY_CURRENT_USER
  if (!bOpened)
    return;

  try
  {
    Reg->WriteInteger(keyName, iVal);
  }
  catch(...) {}
}
//---------------------------------------------------------------------------


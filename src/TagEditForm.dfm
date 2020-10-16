object FormTags: TFormTags
  Left = 0
  Top = 0
  Caption = 'SwiftMiX Tag Editor'
  ClientHeight = 236
  ClientWidth = 579
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Icon.Data = {
    000001000200101010000000000028010000260000002020100000000000E802
    00004E0100002800000010000000200000000100040000000000C00000000000
    0000000000000000000000000000000000000000800000800000008080008000
    0000800080008080000080808000C0C0C0000000FF0000FF000000FFFF00FF00
    0000FF00FF00FFFF0000FFFFFF00F000000000000000F888888888888880F777
    777777777780F7BE00000000DB80F7BBE000000DBB80F7B0BE7888DB0B80F7B0
    0B7008B00B80F7B0097008900B80F7B0097F08900B80F7B00B7778B00B80F7B0
    BD0000EB0B80F7BBD000000EBB80F7BD00000000EB80F788888888888880F777
    777777777780FFFFFFFFFFFFFFFF0000000000000000000000000FF0000007E0
    0000000000000180000001800000008000000000000003C0000007E000000FF0
    0000000000000000000000000000280000002000000040000000010004000000
    0000800200000000000000000000000000000000000000000000000080000080
    00000080800080000000800080008080000080808000C0C0C0000000FF0000FF
    000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0000000000000000000000
    000000000000F7888888888888888888888888888880F7877777777777777777
    777777777780F78E000000000000000000000000D780F78BE000000000000000
    0000000DB780F78BBE00000000000000000000DBB780F78B0BE0000000000000
    00000DB0B780F78B00BE0000000000000000DB00B780F78B000BE00000000000
    000DB000B780F78B0000BE000000000000DB0000B780F78B00000BE000000000
    0DB00000B780F78B000000B7888888888B000000B780F78B0000009787777777
    89000000B780F78B000000978F00000789000000B780F78B000000978F000007
    89000000B780F78B000000978F00000789000000B780F78B000000978F000007
    89000000B780F78B000000978F00000789000000B780F78B000000978FFFFF07
    89000000B780F78B000000978888888789000000B780F78B000000B777777777
    8B000000B780F78B00000BD0000000000EB00000B780F78B0000BD0000000000
    00EB0000B780F78B000BD00000000000000EB000B780F78B00BD000000000000
    0000EB00B780F78B0BD000000000000000000EB0B780F78BBD00000000000000
    000000EBB780F78BD0000000000000000000000EB780F78D0000000000000000
    00000000E780F7888888888888888888888888888780F7777777777777777777
    777777777780FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000000000000000
    00000FFFFFF007FFFFE003FFFFC001FFFF8000FFFF00007FFE00003FFC00001F
    F8000000000000000000000000000003C0000003C0000003C0000003C0000000
    00000000000000000000001FF800003FFC00007FFE0000FFFF0001FFFF8003FF
    FFC007FFFFE00FFFFFF0000000000000000000000000}
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object LabelPath: TLabel
    Left = 0
    Top = 210
    Width = 579
    Height = 13
    Align = alTop
    Caption = 'LabelPath'
    ExplicitWidth = 47
  end
  object LabelCredit: TLabel
    Left = 0
    Top = 223
    Width = 579
    Height = 13
    Align = alTop
    Caption = 'LabelCredit'
    ExplicitWidth = 54
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 0
    Width = 579
    Height = 210
    Align = alTop
    Caption = 'File properties'
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 27
      Width = 20
      Height = 13
      Caption = 'Title'
    end
    object Label2: TLabel
      Left = 16
      Top = 54
      Width = 26
      Height = 13
      Caption = 'Artist'
    end
    object Label4: TLabel
      Left = 16
      Top = 81
      Width = 29
      Height = 13
      Caption = 'Album'
    end
    object Label3: TLabel
      Left = 16
      Top = 109
      Width = 29
      Height = 13
      Caption = 'Genre'
    end
    object Label6: TLabel
      Left = 144
      Top = 136
      Width = 26
      Height = 13
      Caption = 'Track'
    end
    object Label5: TLabel
      Left = 16
      Top = 136
      Width = 22
      Height = 13
      Caption = 'Year'
    end
    object EdtTitle: TEdit
      Left = 72
      Top = 24
      Width = 177
      Height = 21
      TabOrder = 0
    end
    object EdtArtist: TEdit
      Left = 72
      Top = 51
      Width = 177
      Height = 21
      TabOrder = 1
    end
    object EdtAlbum: TEdit
      Left = 72
      Top = 78
      Width = 177
      Height = 21
      TabOrder = 2
    end
    object EdtGenre: TEdit
      Left = 72
      Top = 106
      Width = 177
      Height = 21
      TabOrder = 3
    end
    object EdtYear: TEdit
      Left = 72
      Top = 133
      Width = 57
      Height = 21
      TabOrder = 4
    end
    object EdtTrack: TEdit
      Left = 176
      Top = 133
      Width = 73
      Height = 21
      TabOrder = 5
    end
    object Memo1: TMemo
      Left = 264
      Top = 24
      Width = 297
      Height = 103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 6
    end
    object BtnSave: TButton
      Left = 104
      Top = 168
      Width = 97
      Height = 25
      Caption = 'Save changes'
      TabOrder = 7
      OnClick = BtnSaveClick
    end
    object ButtonCopyTags: TButton
      Left = 288
      Top = 152
      Width = 97
      Height = 25
      Caption = 'Copy Tags'
      TabOrder = 8
      OnClick = ButtonCopyTagsClick
    end
    object ButtonPasteTags: TButton
      Left = 432
      Top = 152
      Width = 97
      Height = 25
      Caption = 'Paste Tags'
      TabOrder = 9
      OnClick = ButtonPasteTagsClick
    end
  end
end

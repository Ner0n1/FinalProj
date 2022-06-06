object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 392
  ClientWidth = 548
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  PixelsPerInch = 96
  TextHeight = 15
  object Label1: TLabel
    Left = 8
    Top = 3
    Width = 35
    Height = 15
    Caption = 'Target:'
  end
  object Label2: TLabel
    Left = 256
    Top = 11
    Width = 42
    Height = 15
    Caption = 'FS Type:'
  end
  object Label3: TLabel
    Left = 256
    Top = 32
    Width = 87
    Height = 15
    Caption = 'Bytes per Sector:'
  end
  object Label4: TLabel
    Left = 256
    Top = 53
    Width = 101
    Height = 15
    Caption = 'Sectors per Cluster:'
  end
  object Label5: TLabel
    Left = 256
    Top = 74
    Width = 91
    Height = 15
    Caption = 'Bytes per Cluster:'
  end
  object Label6: TLabel
    Left = 256
    Top = 95
    Width = 73
    Height = 15
    Caption = 'Total Clusters:'
  end
  object Label7: TLabel
    Left = 376
    Top = 11
    Width = 5
    Height = 15
    Caption = '-'
  end
  object Label8: TLabel
    Left = 376
    Top = 32
    Width = 5
    Height = 15
    Caption = '-'
  end
  object Label9: TLabel
    Left = 376
    Top = 53
    Width = 5
    Height = 15
    Caption = '-'
  end
  object Label10: TLabel
    Left = 376
    Top = 74
    Width = 5
    Height = 15
    Caption = '-'
  end
  object Label11: TLabel
    Left = 376
    Top = 95
    Width = 5
    Height = 15
    Caption = '-'
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 126
    Width = 425
    Height = 251
    Header.AutoSizeIndex = 0
    TabOrder = 0
    OnAddToSelection = VirtualStringTree1AddToSelection
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'Signature'
      end
      item
        Position = 1
        Text = 'Cluster'
      end>
  end
  object Edit1: TEdit
    Left = 8
    Top = 24
    Width = 81
    Height = 23
    TabOrder = 1
    Text = '\\.\C:'
  end
  object Button1: TButton
    Left = 120
    Top = 24
    Width = 81
    Height = 23
    Caption = 'Enter Path'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 470
    Top = 352
    Width = 75
    Height = 25
    Caption = 'Exit'
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 8
    Top = 64
    Width = 81
    Height = 25
    Caption = 'Searching'
    Enabled = False
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 120
    Top = 64
    Width = 81
    Height = 25
    Caption = 'Stop Searching'
    Enabled = False
    TabOrder = 5
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 448
    Top = 176
    Width = 97
    Height = 25
    Caption = 'Clear Table'
    TabOrder = 6
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 448
    Top = 135
    Width = 97
    Height = 24
    Caption = 'Delete Selected'
    Enabled = False
    TabOrder = 7
    OnClick = Button6Click
  end
  object CheckBox1: TCheckBox
    Left = 8
    Top = 103
    Width = 161
    Height = 17
    Caption = 'Ignore Empty Clusters'
    Checked = True
    State = cbChecked
    TabOrder = 8
  end
end

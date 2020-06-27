; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFireWallView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FireWall.h"
LastPage=0

ClassCount=5
Class1=CFireWallApp
Class2=CFireWallDoc
Class3=CFireWallView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_FIREWALL_FORM
Class5=CAboutDlg
Resource4=IDD_ADDRULEDLG

[CLS:CFireWallApp]
Type=0
HeaderFile=FireWall.h
ImplementationFile=FireWall.cpp
Filter=N
LastObject=CFireWallApp

[CLS:CFireWallDoc]
Type=0
HeaderFile=FireWallDoc.h
ImplementationFile=FireWallDoc.cpp
Filter=N
LastObject=CFireWallDoc

[CLS:CFireWallView]
Type=0
HeaderFile=FireWallView.h
ImplementationFile=FireWallView.cpp
Filter=D
LastObject=IDC_LIST_RULES


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=FireWall.cpp
ImplementationFile=FireWall.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_MENUSTART
Command2=ID_MENUSTOP
Command3=IDMENU_LOADRULES
Command4=IDMENU_SAVERULES
Command5=ID_APP_EXIT
Command6=IDMENU_ADDRULE
Command7=IDMENU_DELRULE
Command8=IDMENU_INSTALLRULES
Command9=IDMENU_UNINSTALLRULES
Command10=ID_APP_ABOUT
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_FIREWALL_FORM]
Type=1
Class=CFireWallView
ControlCount=2
Control1=IDC_STATIC,button,1342177287
Control2=IDC_LIST_RULES,SysListView32,1350631425

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_BUTTONSTART
Command2=ID_BUTTONSTOP
Command3=ID_BUTTONADD
Command4=ID_BUTTONDEL
Command5=ID_BUTTONINSTALL
Command6=ID_BUTTONUNINSTALL
CommandCount=6

[DLG:IDD_ADDRULEDLG]
Type=1
Class=?
ControlCount=24
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_DEST_IP,edit,1350631554
Control14=IDC_DEST_MASK,edit,1350631554
Control15=IDC_SOURCE_MASK,edit,1350631554
Control16=IDC_SOURCE_PORT,edit,1350631554
Control17=IDC_DEST_PORT,edit,1350631554
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDOK,button,1342242816
Control21=IDCANCEL,button,1342242816
Control22=IDC_PROTOCOL,combobox,1344340226
Control23=IDC_ACTION,combobox,1344340226
Control24=IDC_SOURCE_IP,edit,1350631554


// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FireWall.h"

#include "MainFrm.h"
#include "RuleDlg.h"
#include "FireWallDoc.h"
#include "FireWallView.h"
#include "SockUtil.h"
#include "Rules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_BUTTONADD, OnButtonadd)
	ON_COMMAND(ID_BUTTONDEL, OnButtondel)
	ON_COMMAND(ID_BUTTONSTART, OnButtonstart)
	ON_COMMAND(ID_BUTTONSTOP, OnButtonstop)
	ON_COMMAND(ID_BUTTONUNINSTALL, OnButtonuninstall)
	ON_COMMAND(IDMENU_ADDRULE, OnMenuAddRule)
	ON_COMMAND(IDMENU_DELRULE, OnMenuDelRule)
	ON_COMMAND(IDMENU_INSTALLRULES, OnMenuInstallRules)
	ON_COMMAND(ID_MENUSTART, OnMenuStart)
	ON_COMMAND(ID_MENUSTOP, OnMenuStop)
	ON_COMMAND(IDMENU_SAVERULES, OnMenuSaveRules)
	ON_COMMAND(IDMENU_UNINSTALLRULES, OnMenuUninstallRules)
	ON_COMMAND(IDMENU_LOADRULES, OnMenuLoadRules)
	ON_UPDATE_COMMAND_UI(ID_BUTTONSTART, OnUpdateButtonStart)
	ON_UPDATE_COMMAND_UI(ID_BUTTONSTOP, OnUpdateButtonStop)
	ON_UPDATE_COMMAND_UI(ID_MENUSTART, OnUpdateMenuStart)
	ON_UPDATE_COMMAND_UI(ID_MENUSTOP, OnUpdateMenuStop)
	ON_COMMAND(ID_BUTTONINSTALL, OnButtonInstall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()//初始化加载驱动
{
	started = FALSE;
	Installed = FALSE;

	ipFltDrv.LoadDriver("IpFilterDriver", "System32\\Drivers\\IpFltDrv.sys", NULL, TRUE);//加载驱动

	ipFltDrv.SetRemovable(FALSE);

	if(filterDriver.LoadDriver("DrvFltIp", NULL, NULL, TRUE) != DRV_SUCCESS)
	{
		AfxMessageBox("加载驱动出错");

		exit(-1);
	}
	
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
	started = FALSE;
	ipFltDrv.LoadDriver("IpFilterDriver", "System32\\Drivers\\IpFltDrv.sys", NULL, TRUE);
	ipFltDrv.SetRemovable(FALSE);
	if(filterDriver.LoadDriver("DrvFltIp", NULL, NULL, TRUE) != DRV_SUCCESS)
	{
		AfxMessageBox("加载驱动出错");

		exit(-1);
	}
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)//创建主窗口
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	SetWindowText("简易windows防火墙");
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~ FWS_ADDTOTITLE;


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::AddFilterToFw(unsigned long srcIp, 
					   unsigned long srcMask,
					   unsigned short srcPort, 
					   unsigned long dstIp,
					   unsigned long dstMask,
					   unsigned short dstPort,
					   unsigned int porotol,
					   int action)   //安装过滤钩子
{
	IPFilter pf;


	pf.protocol = porotol;

	pf.destinationIp = dstIp;			
	pf.sourceIp		 = srcIp;

	pf.destinationMask = dstMask;	
	pf.sourceMask	   = srcMask;		

	pf.destinationPort = htons(dstPort);						
	pf.sourcePort	   = htons(srcPort);				

	pf.drop = action;		
	
	
	DWORD result = filterDriver.WriteIo(ADD_FILTER, &pf, sizeof(pf));

	if (result != DRV_SUCCESS) 
	{
		AfxMessageBox("安装钩子失败");

		return FALSE;
	}

	else
		return TRUE;
}

void CMainFrame::OnAppExit() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtonadd()   //添加规则
{
	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();
	CRuleDlg dlg;

	if(doc->nRules < MAX_RULES )   //过滤规则数未达到最大数目
	{
		if(dlg.DoModal() == IDOK)
		{
		
			if(doc->AddRule(dlg.srcIp, dlg.srcMask, dlg.srcPort, dlg.dstIp, dlg.dstMask,
			                dlg.dstPort, dlg.protocol, dlg.cAction) == FALSE)  //添加失败
				AfxMessageBox("添加过滤规则失败");
			else
			{
				CFireWallView *view = (CFireWallView *)GetActiveView();

				view->UpdateList();
			}
		}
	}
	else    //过滤规则数达到最大数目
		AfxMessageBox("你不能再添加规则了");

	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtondel()  //删除规则
{
	CFireWallView *view = (CFireWallView *)GetActiveView();
	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();
	POSITION pos = view->m_rules.GetFirstSelectedItemPosition();  //指向选中的规则
	if(doc->nRules <=0 )   //没有规则
	{
		AfxMessageBox("过滤规则0条");
		return;
	}
	else 
	{
		if (pos == NULL)    //规则未选中
		{
			AfxMessageBox("请选择要删除的规则");
			return;
		}
		else if(started == TRUE)   //正在进行过滤
		{	
			CString strTemp;
			strTemp.Format("确定要删除该条规则吗？");
			if(MessageBox(strTemp,"删除规则",MB_YESNO|MB_ICONQUESTION)==IDNO)
				return;
			else
				OnButtonstop();   //先停止过滤
		}
		
	}
	int position;
	position = view->m_rules.GetNextSelectedItem(pos);   //position为当前选中规则序数nRules+1

	CFireWallDoc *doco = (CFireWallDoc *)GetActiveDocument();
	doco->DeleteRule(position);    //调用DeleteRule(),将当前规则以后的所以规则向前移动1，即删除当前规则


	// Actualizo la vista
	view->UpdateList();        //刷新列表
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnButtonstart()   //开始过滤
{
	CFireWallDoc *doco = (CFireWallDoc *)GetActiveDocument();  //从存放规则的文档中获取数据
	if(doco->nRules <=0 )   //没有规则
	{
		AfxMessageBox("请先添加过滤规则");
		started = FALSE;
	}
	else if(Installed == FALSE)   //没有安装
	{
		AfxMessageBox("你的过滤规则尚未被安装");
	}
	else if(filterDriver.WriteIo(START_IP_HOOK, NULL, 0) != DRV_ERROR_IO)
	{
		started = TRUE;
	}// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtonstop()    //停止过滤
{
	if(filterDriver.WriteIo(STOP_IP_HOOK, NULL, 0) != DRV_ERROR_IO)
	{
		started = FALSE;
	}	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtonInstall()   //安装规则
{
	CFireWallDoc *doco = (CFireWallDoc *)GetActiveDocument();
	if(doco->nRules <=0 )    //没有规则
		AfxMessageBox("请先添加过滤规则");

	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();
	unsigned int i;
	DWORD result;

	for(i=0;i<doc->nRules;i++)   //依次安装每条规则
	{
		result = AddFilterToFw(doc->rules[i].sourceIp, 
							   doc->rules[i].sourceMask,
							   doc->rules[i].sourcePort,
							   doc->rules[i].destinationIp,
							   doc->rules[i].destinationMask,
							   doc->rules[i].destinationPort,
							   doc->rules[i].protocol, 
							   doc->rules[i].action);

		if (!result) 
			break;
		Installed = TRUE;
	}
	
}

void CMainFrame::OnButtonuninstall()   //卸载规则
{
	CFireWallDoc *doco = (CFireWallDoc *)GetActiveDocument();
	if(doco->nRules <=0 )        
		AfxMessageBox("你还没有安装过滤规则");

	if(filterDriver.WriteIo(CLEAR_FILTER, NULL, 0) == DRV_ERROR_IO)
	{
		AfxMessageBox("卸载失败");
	}
	// TODO: Add your command handler code here
	
}



void CMainFrame::OnMenuAddRule() //
{
	OnButtonadd();	// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuDelRule() //
{
	OnButtondel();// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuInstallRules() //
{
	OnButtonInstall();// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuStart() //
{
	OnButtonstart();// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuStop() //
{
	OnButtonstop();// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuSaveRules()   //保存规则
{
	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();

	if(doc->nRules == 0)
	{
		AfxMessageBox("你还没有添加过滤规则");

		return;
	}


	CFileDialog dg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_CREATEPROMPT,"Rule Files(*.rul)|*.rul|all(*.*)|*.*||", NULL);
	if(dg.DoModal()==IDCANCEL)   //取消
		return;
	
	CString nf=dg.GetPathName();   //nf取得保存路径

	if(nf.GetLength() == 0)
	{
		AfxMessageBox("请选择有效的文件");

		return;
	}

	CFile file;
	CFileException e;
	
	if( !file.Open( nf, CFile::modeCreate | CFile::modeWrite, &e ) )  //新建可写文件
	{
		AfxMessageBox("打开文件失败");

		return;
	}


	unsigned int i;

	for(i=0;i<doc->nRules;i++)   //依次写入第1-nRules条规则
	{
		file.Write(&doc->rules[i], sizeof(RuleInfo));
	}
	
	file.Close();   //关闭文件
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuUninstallRules() //
{
	OnButtonuninstall();// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuLoadRules()   //加载规则
{
	CFile file;
	CFileException e;
	DWORD nRead;

	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();

	CFileDialog dg(TRUE,NULL, NULL, OFN_HIDEREADONLY |
				   OFN_CREATEPROMPT,"Rule Files(*.rul)|*.rul|all(*.*)|*.*||", NULL);
	if(dg.DoModal()==IDCANCEL)   //取消
		return;
	
	CString nf=dg.GetPathName();

	if(nf.GetLength() == 0)
	{
		AfxMessageBox("请选择有效的文件.");

		return;
	}

	if( !file.Open(nf, CFile::modeRead, &e ) )
	{
		AfxMessageBox("打开文件失败.");

		return;
	}

	doc->ResetRules();   //加载时清除现有规则
	RuleInfo rule;

    do  //依次加载文件中的规则
    {
 		nRead = file.Read(&rule, sizeof(RuleInfo));
		
		if(nRead == 0)
			break;

		if(doc->AddRule(rule.sourceIp,
				        rule.sourceMask,
						rule.sourcePort,
						rule.destinationIp,
						rule.destinationMask,
						rule.destinationPort,
						rule.protocol,				   
						rule.action)  != 0)
		{

			AfxMessageBox("加载规则成功.");

			break;
		}
    }while (1);

	CFireWallView *view = (CFireWallView *)GetActiveView();

	view->UpdateList();
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateButtonStart(CCmdUI* pCmdUI)//
{
	if(started)
		pCmdUI->Enable(FALSE);   //“开始”按钮不可用

	else
		pCmdUI->Enable(TRUE);	//“开始”按钮可用
}

void CMainFrame::OnUpdateButtonStop(CCmdUI* pCmdUI)//
{
	if(started)
		pCmdUI->Enable(TRUE);  //“停止”按钮可用

	else
		pCmdUI->Enable(FALSE); //“停止”按钮不可用
}

void CMainFrame::OnUpdateMenuStop(CCmdUI* pCmdUI)//
{
	if(started)
		pCmdUI->Enable(TRUE);//“停止过滤”菜单可用

	else
		pCmdUI->Enable(FALSE);//“停止过滤”菜单不可用
}

void CMainFrame::OnUpdateMenuStart(CCmdUI* pCmdUI)//
{
	if(started)
		pCmdUI->Enable(FALSE);  //“开始过滤”菜单不可用

	else
		pCmdUI->Enable(TRUE);	//“开始过滤”菜单可用
}


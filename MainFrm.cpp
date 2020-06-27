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

CMainFrame::CMainFrame()//��ʼ����������
{
	started = FALSE;
	Installed = FALSE;

	ipFltDrv.LoadDriver("IpFilterDriver", "System32\\Drivers\\IpFltDrv.sys", NULL, TRUE);//��������

	ipFltDrv.SetRemovable(FALSE);

	if(filterDriver.LoadDriver("DrvFltIp", NULL, NULL, TRUE) != DRV_SUCCESS)
	{
		AfxMessageBox("������������");

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
		AfxMessageBox("������������");

		exit(-1);
	}
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)//����������
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

	SetWindowText("����windows����ǽ");
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
					   int action)   //��װ���˹���
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
		AfxMessageBox("��װ����ʧ��");

		return FALSE;
	}

	else
		return TRUE;
}

void CMainFrame::OnAppExit() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtonadd()   //��ӹ���
{
	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();
	CRuleDlg dlg;

	if(doc->nRules < MAX_RULES )   //���˹�����δ�ﵽ�����Ŀ
	{
		if(dlg.DoModal() == IDOK)
		{
		
			if(doc->AddRule(dlg.srcIp, dlg.srcMask, dlg.srcPort, dlg.dstIp, dlg.dstMask,
			                dlg.dstPort, dlg.protocol, dlg.cAction) == FALSE)  //���ʧ��
				AfxMessageBox("��ӹ��˹���ʧ��");
			else
			{
				CFireWallView *view = (CFireWallView *)GetActiveView();

				view->UpdateList();
			}
		}
	}
	else    //���˹������ﵽ�����Ŀ
		AfxMessageBox("�㲻������ӹ�����");

	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtondel()  //ɾ������
{
	CFireWallView *view = (CFireWallView *)GetActiveView();
	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();
	POSITION pos = view->m_rules.GetFirstSelectedItemPosition();  //ָ��ѡ�еĹ���
	if(doc->nRules <=0 )   //û�й���
	{
		AfxMessageBox("���˹���0��");
		return;
	}
	else 
	{
		if (pos == NULL)    //����δѡ��
		{
			AfxMessageBox("��ѡ��Ҫɾ���Ĺ���");
			return;
		}
		else if(started == TRUE)   //���ڽ��й���
		{	
			CString strTemp;
			strTemp.Format("ȷ��Ҫɾ������������");
			if(MessageBox(strTemp,"ɾ������",MB_YESNO|MB_ICONQUESTION)==IDNO)
				return;
			else
				OnButtonstop();   //��ֹͣ����
		}
		
	}
	int position;
	position = view->m_rules.GetNextSelectedItem(pos);   //positionΪ��ǰѡ�й�������nRules+1

	CFireWallDoc *doco = (CFireWallDoc *)GetActiveDocument();
	doco->DeleteRule(position);    //����DeleteRule(),����ǰ�����Ժ�����Թ�����ǰ�ƶ�1����ɾ����ǰ����


	// Actualizo la vista
	view->UpdateList();        //ˢ���б�
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnButtonstart()   //��ʼ����
{
	CFireWallDoc *doco = (CFireWallDoc *)GetActiveDocument();  //�Ӵ�Ź�����ĵ��л�ȡ����
	if(doco->nRules <=0 )   //û�й���
	{
		AfxMessageBox("������ӹ��˹���");
		started = FALSE;
	}
	else if(Installed == FALSE)   //û�а�װ
	{
		AfxMessageBox("��Ĺ��˹�����δ����װ");
	}
	else if(filterDriver.WriteIo(START_IP_HOOK, NULL, 0) != DRV_ERROR_IO)
	{
		started = TRUE;
	}// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtonstop()    //ֹͣ����
{
	if(filterDriver.WriteIo(STOP_IP_HOOK, NULL, 0) != DRV_ERROR_IO)
	{
		started = FALSE;
	}	// TODO: Add your command handler code here
	
}

void CMainFrame::OnButtonInstall()   //��װ����
{
	CFireWallDoc *doco = (CFireWallDoc *)GetActiveDocument();
	if(doco->nRules <=0 )    //û�й���
		AfxMessageBox("������ӹ��˹���");

	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();
	unsigned int i;
	DWORD result;

	for(i=0;i<doc->nRules;i++)   //���ΰ�װÿ������
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

void CMainFrame::OnButtonuninstall()   //ж�ع���
{
	CFireWallDoc *doco = (CFireWallDoc *)GetActiveDocument();
	if(doco->nRules <=0 )        
		AfxMessageBox("�㻹û�а�װ���˹���");

	if(filterDriver.WriteIo(CLEAR_FILTER, NULL, 0) == DRV_ERROR_IO)
	{
		AfxMessageBox("ж��ʧ��");
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

void CMainFrame::OnMenuSaveRules()   //�������
{
	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();

	if(doc->nRules == 0)
	{
		AfxMessageBox("�㻹û����ӹ��˹���");

		return;
	}


	CFileDialog dg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_CREATEPROMPT,"Rule Files(*.rul)|*.rul|all(*.*)|*.*||", NULL);
	if(dg.DoModal()==IDCANCEL)   //ȡ��
		return;
	
	CString nf=dg.GetPathName();   //nfȡ�ñ���·��

	if(nf.GetLength() == 0)
	{
		AfxMessageBox("��ѡ����Ч���ļ�");

		return;
	}

	CFile file;
	CFileException e;
	
	if( !file.Open( nf, CFile::modeCreate | CFile::modeWrite, &e ) )  //�½���д�ļ�
	{
		AfxMessageBox("���ļ�ʧ��");

		return;
	}


	unsigned int i;

	for(i=0;i<doc->nRules;i++)   //����д���1-nRules������
	{
		file.Write(&doc->rules[i], sizeof(RuleInfo));
	}
	
	file.Close();   //�ر��ļ�
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuUninstallRules() //
{
	OnButtonuninstall();// TODO: Add your command handler code here
	
}

void CMainFrame::OnMenuLoadRules()   //���ع���
{
	CFile file;
	CFileException e;
	DWORD nRead;

	CFireWallDoc *doc = (CFireWallDoc *)GetActiveDocument();

	CFileDialog dg(TRUE,NULL, NULL, OFN_HIDEREADONLY |
				   OFN_CREATEPROMPT,"Rule Files(*.rul)|*.rul|all(*.*)|*.*||", NULL);
	if(dg.DoModal()==IDCANCEL)   //ȡ��
		return;
	
	CString nf=dg.GetPathName();

	if(nf.GetLength() == 0)
	{
		AfxMessageBox("��ѡ����Ч���ļ�.");

		return;
	}

	if( !file.Open(nf, CFile::modeRead, &e ) )
	{
		AfxMessageBox("���ļ�ʧ��.");

		return;
	}

	doc->ResetRules();   //����ʱ������й���
	RuleInfo rule;

    do  //���μ����ļ��еĹ���
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

			AfxMessageBox("���ع���ɹ�.");

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
		pCmdUI->Enable(FALSE);   //����ʼ����ť������

	else
		pCmdUI->Enable(TRUE);	//����ʼ����ť����
}

void CMainFrame::OnUpdateButtonStop(CCmdUI* pCmdUI)//
{
	if(started)
		pCmdUI->Enable(TRUE);  //��ֹͣ����ť����

	else
		pCmdUI->Enable(FALSE); //��ֹͣ����ť������
}

void CMainFrame::OnUpdateMenuStop(CCmdUI* pCmdUI)//
{
	if(started)
		pCmdUI->Enable(TRUE);//��ֹͣ���ˡ��˵�����

	else
		pCmdUI->Enable(FALSE);//��ֹͣ���ˡ��˵�������
}

void CMainFrame::OnUpdateMenuStart(CCmdUI* pCmdUI)//
{
	if(started)
		pCmdUI->Enable(FALSE);  //����ʼ���ˡ��˵�������

	else
		pCmdUI->Enable(TRUE);	//����ʼ���ˡ��˵�����
}


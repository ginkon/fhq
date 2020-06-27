// RuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FireWall.h"
#include "RuleDlg.h"

#include "sockUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuleDlg dialog


CRuleDlg::CRuleDlg(CWnd* pParent /*=NULL*/) 
	: CDialog(CRuleDlg::IDD, pParent) //设置对话框缺省值
{
	//缺省过滤规则：所有丢弃
	m_ipsource = _T("0.0.0.0");         
	m_portsource = 0;                   
	m_ipdestination = _T("0.0.0.0");

	m_portDestination = 0;
	m_srcMask = _T("255.255.255.255");
	m_dstMask = _T("255.255.255.255");

	m_protocol = _T("所有");
	m_action = _T("丢弃");
	//}}AFX_DATA_INIT
}


void CRuleDlg::DoDataExchange(CDataExchange* pDX)//
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleDlg)
	DDX_Text(pDX, IDC_SOURCE_IP, m_ipsource);
	DDV_MaxChars(pDX, m_ipsource, 15);
	DDX_Text(pDX, IDC_SOURCE_PORT, m_portsource);
	DDX_Text(pDX, IDC_DEST_IP, m_ipdestination);
	DDV_MaxChars(pDX, m_ipdestination, 15);
	DDX_Text(pDX, IDC_DEST_PORT, m_portDestination);
	DDX_CBString(pDX, IDC_ACTION, m_action);
	DDX_CBString(pDX, IDC_PROTOCOL, m_protocol);
	DDX_Text(pDX, IDC_SOURCE_MASK, m_srcMask);
	DDV_MaxChars(pDX, m_srcMask, 15);
	DDX_Text(pDX, IDC_DEST_MASK, m_dstMask);
	DDV_MaxChars(pDX, m_dstMask, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleDlg, CDialog)
	//{{AFX_MSG_MAP(CRuleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleDlg message handlers

void CRuleDlg::OnOK() //取得编辑框中的数据，赋给变量
{
	int result;

	UpdateData(TRUE);    //控件变量与控件关联

	result = inet_addr(m_ipsource, &srcIp);  //从源IP地址编辑框取得源IP地址赋给srcIp，
											 //失败则返回-1

	if(result == -1)
	{
		AfxMessageBox("请输入正确的源IP地址");

		return;
	}

	result = inet_addr(m_srcMask, &srcMask);

	if(result == -1)
	{
		AfxMessageBox("请输入正确的源地址子网掩码");

		return;
	}


	result = inet_addr(m_ipdestination, &dstIp);//从目的IP地址编辑框取得目的IP地址赋给m_ipsestination，失败则返回-1

	if(result == -1)
	{
		AfxMessageBox("请输入正确的目的IP地址");

		return;
	}

	result = inet_addr(m_dstMask, &dstMask);

	if(result == -1)
	{
		AfxMessageBox("请输入正确的目的地址子网掩码");

		return;
	}


	if(m_protocol == "TCP")
		protocol = 6;

	else if(m_protocol == "UDP")
		protocol = 17;

	else if(m_protocol == "ICMP")
		protocol = 1;

	else if(m_protocol == "所有")
		protocol = 0;
	
//	else if(m_protocol == "")
//	{
//		AfxMessageBox("请选择需要过滤的协议");

//		return;
//	}

//	if(m_action == "")
//	{
//		AfxMessageBox("请选择操作行为");

//		return;
//	}

	else 
	{
		if(m_action == "放行")
			cAction = 0;

		else
			cAction = 1;

	}

	srcPort = m_portsource;
	dstPort = m_portDestination;
	
	CDialog::OnOK();
}

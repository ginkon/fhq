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
	: CDialog(CRuleDlg::IDD, pParent) //���öԻ���ȱʡֵ
{
	//ȱʡ���˹������ж���
	m_ipsource = _T("0.0.0.0");         
	m_portsource = 0;                   
	m_ipdestination = _T("0.0.0.0");

	m_portDestination = 0;
	m_srcMask = _T("255.255.255.255");
	m_dstMask = _T("255.255.255.255");

	m_protocol = _T("����");
	m_action = _T("����");
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

void CRuleDlg::OnOK() //ȡ�ñ༭���е����ݣ���������
{
	int result;

	UpdateData(TRUE);    //�ؼ�������ؼ�����

	result = inet_addr(m_ipsource, &srcIp);  //��ԴIP��ַ�༭��ȡ��ԴIP��ַ����srcIp��
											 //ʧ���򷵻�-1

	if(result == -1)
	{
		AfxMessageBox("��������ȷ��ԴIP��ַ");

		return;
	}

	result = inet_addr(m_srcMask, &srcMask);

	if(result == -1)
	{
		AfxMessageBox("��������ȷ��Դ��ַ��������");

		return;
	}


	result = inet_addr(m_ipdestination, &dstIp);//��Ŀ��IP��ַ�༭��ȡ��Ŀ��IP��ַ����m_ipsestination��ʧ���򷵻�-1

	if(result == -1)
	{
		AfxMessageBox("��������ȷ��Ŀ��IP��ַ");

		return;
	}

	result = inet_addr(m_dstMask, &dstMask);

	if(result == -1)
	{
		AfxMessageBox("��������ȷ��Ŀ�ĵ�ַ��������");

		return;
	}


	if(m_protocol == "TCP")
		protocol = 6;

	else if(m_protocol == "UDP")
		protocol = 17;

	else if(m_protocol == "ICMP")
		protocol = 1;

	else if(m_protocol == "����")
		protocol = 0;
	
//	else if(m_protocol == "")
//	{
//		AfxMessageBox("��ѡ����Ҫ���˵�Э��");

//		return;
//	}

//	if(m_action == "")
//	{
//		AfxMessageBox("��ѡ�������Ϊ");

//		return;
//	}

	else 
	{
		if(m_action == "����")
			cAction = 0;

		else
			cAction = 1;

	}

	srcPort = m_portsource;
	dstPort = m_portDestination;
	
	CDialog::OnOK();
}

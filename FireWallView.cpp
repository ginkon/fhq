// FireWallView.cpp : implementation of the CFireWallView class
//

#include "stdafx.h"
#include "FireWall.h"

#include "FireWallDoc.h"
#include "FireWallView.h"
#include "SockUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFireWallView

IMPLEMENT_DYNCREATE(CFireWallView, CFormView)

BEGIN_MESSAGE_MAP(CFireWallView, CFormView)
	//{{AFX_MSG_MAP(CFireWallView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFireWallView construction/destruction

CFireWallView::CFireWallView()
	: CFormView(CFireWallView::IDD)
{
	//{{AFX_DATA_INIT(CFireWallView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CFireWallView::~CFireWallView()
{
}

void CFireWallView::DoDataExchange(CDataExchange* pDX)//
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFireWallView)
	DDX_Control(pDX, IDC_LIST_RULES, m_rules);	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CFireWallView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CFireWallView::OnInitialUpdate()//初始化
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	m_rules.InsertColumn(0, "源IP地址",LVCFMT_LEFT , 100, 0);
	m_rules.InsertColumn(1, "子网掩码",LVCFMT_LEFT , 110, 1);
	m_rules.InsertColumn(2, "源端口",LVCFMT_LEFT ,50, 2);
	m_rules.InsertColumn(3, "目的IP地址",LVCFMT_LEFT , 110, 3);
	m_rules.InsertColumn(4, "子网掩码",LVCFMT_LEFT , 110, 4);
	m_rules.InsertColumn(5, "目的端口",LVCFMT_LEFT , 60, 5);
	m_rules.InsertColumn(6, "协议",LVCFMT_LEFT ,40, 6);
	m_rules.InsertColumn(7, "行为",LVCFMT_LEFT , 40, 7);
	m_rules.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

/////////////////////////////////////////////////////////////////////////////
// CFireWallView printing

BOOL CFireWallView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFireWallView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFireWallView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFireWallView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CFireWallView diagnostics

#ifdef _DEBUG
void CFireWallView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFireWallView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFireWallDoc* CFireWallView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFireWallDoc)));
	return (CFireWallDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFireWallView message handlers


void CFireWallView::AddRuleToList(unsigned long srcIp, 
					   unsigned long srcMask,
					   unsigned short srcPort, 
					   unsigned long dstIp, 
					   unsigned long dstMask,
					   unsigned short dstPort, 
					   unsigned int protocol, 
					   int action)//
{
	char ip[16];
	char port[6];
	LVITEM it;
	int pos;

	
	it.mask		= LVIF_TEXT;
	it.iItem	= m_rules.GetItemCount();
	it.iSubItem	= 0;
	it.pszText	= (srcIp == 0) ? "所有" : IpToString(ip, srcIp);
	pos			= m_rules.InsertItem(&it);

	it.iItem	= pos;
	it.iSubItem	= 1;
	it.pszText	= IpToString(ip, srcMask);
	m_rules.SetItem(&it);

	it.iItem	= pos;
	it.iSubItem	= 2;
	it.pszText	= (srcPort == 0) ? "所有" : itoa(srcPort, port, 10);
	m_rules.SetItem(&it);
	
	it.iItem	= pos;
	it.iSubItem	= 3;
	it.pszText	= (dstIp == 0) ? "所有" : IpToString(ip, dstIp);
	m_rules.SetItem(&it);

	it.iItem	= pos;
	it.iSubItem	= 4;
	it.pszText	= IpToString(ip, dstMask);
	m_rules.SetItem(&it);

	it.iItem	= pos;
	it.iSubItem = 5;
	it.pszText	= (dstPort == 0) ? "所有" : itoa(dstPort, port, 10);
	m_rules.SetItem(&it);


	it.iItem	= pos;
	it.iSubItem	= 6;
	if(protocol == 1)
		it.pszText = "ICMP";

	else if(protocol == 6)
		it.pszText = "TCP";

	else if(protocol == 17)
		it.pszText = "UDP";

	else
		it.pszText = "所有";
	m_rules.SetItem(&it);

	it.iItem	= pos;
	it.iSubItem	= 7;
	it.pszText = action ? "丢弃" : "放行";
	m_rules.SetItem(&it);

}

void CFireWallView::UpdateList()//更新列表
{
	CFireWallDoc *doc = GetDocument();

	m_rules.DeleteAllItems();

	unsigned int i;
	for(i=0;i<doc->nRules;i++)
	{
		AddRuleToList(doc->rules[i].sourceIp,
					  doc->rules[i].sourceMask,
					  doc->rules[i].sourcePort,
					  doc->rules[i].destinationIp,
					  doc->rules[i].destinationMask,
					  doc->rules[i].destinationPort,
					  doc->rules[i].protocol,
					  doc->rules[i].action);
	}
}

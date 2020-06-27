// FireWallDoc.cpp : implementation of the CFireWallDoc class
//

#include "stdafx.h"
#include "FireWall.h"

#include "FireWallDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFireWallDoc

IMPLEMENT_DYNCREATE(CFireWallDoc, CDocument)

BEGIN_MESSAGE_MAP(CFireWallDoc, CDocument)
	//{{AFX_MSG_MAP(CFireWallDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFireWallDoc construction/destruction

CFireWallDoc::CFireWallDoc()
{
	// TODO: add one-time construction code here
	nRules = 0;

}

CFireWallDoc::~CFireWallDoc()
{

}

BOOL CFireWallDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFireWallDoc serialization

void CFireWallDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFireWallDoc diagnostics

#ifdef _DEBUG
void CFireWallDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFireWallDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFireWallDoc commands

BOOL CFireWallDoc::AddRule(unsigned long srcIp, 
				unsigned long srcMask,
				unsigned short srcPort, 
				unsigned long dstIp,
				unsigned long dstMask,
				unsigned short dstPort,
				unsigned int protocol,
				int action)//
{
	if(nRules >= MAX_RULES)//规则数超过允许最大数
	{
		return FALSE;
	}

	else //添加规则
	{
		rules[nRules].sourceIp		  = srcIp;
		rules[nRules].sourceMask	  = srcMask;
		rules[nRules].sourcePort	  = srcPort;
		rules[nRules].destinationIp   = dstIp;
		rules[nRules].destinationMask = dstMask;
		rules[nRules].destinationPort = dstPort;
		rules[nRules].protocol		  = protocol;
		rules[nRules].action		  = action;

		nRules++;
	}

	return TRUE;
}

void CFireWallDoc::DeleteRule(unsigned int position)//
{
	if(position >= nRules)
		return;

	// Si es la ultima, simplemente tengo que decrementar nRules en 1
	if(position != nRules - 1) //如果删除的规则不是最后一条，则将其删除后，后面的规则往前移动
	{
		unsigned int i;

		for(i = position + 1;i<nRules;i++)
		{
			rules[i - 1].sourceIp		  = rules[i].sourceIp;
			rules[i - 1].sourceMask		  = rules[i].sourceMask;
			rules[i - 1].sourcePort		  = rules[i].sourcePort;
			rules[i - 1].destinationIp    = rules[i].destinationIp;
			rules[i - 1].destinationMask  = rules[i].destinationMask;
			rules[i - 1].destinationPort  = rules[i].destinationPort;
			rules[i - 1].protocol	      = rules[i].protocol;
			rules[i - 1].action		      = rules[i].action;
		}
	}
	nRules--;
}


void CFireWallDoc::ResetRules() //
{
	nRules = 0;
}

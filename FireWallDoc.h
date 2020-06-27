// FireWallDoc.h : interface of the CFireWallDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREWALLDOC_H__99012AD6_A25C_427D_94EC_AA34F9FA9E93__INCLUDED_)
#define AFX_FIREWALLDOC_H__99012AD6_A25C_427D_94EC_AA34F9FA9E93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rules.h"

#define MAX_RULES 15    //最多添加规则数目

class CFireWallDoc : public CDocument
{
protected: // create from serialization only
	CFireWallDoc();
	DECLARE_DYNCREATE(CFireWallDoc)

// Attributes
public:
	unsigned int nRules;   //规则数
	RuleInfo rules[MAX_RULES];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFireWallDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:

	void ResetRules();
	void DeleteRule(unsigned int position);
	int AddRule(unsigned long srcIp, 
				unsigned long srcMask,
				unsigned short srcPort, 
				unsigned long dstIp,
				unsigned long dstMask,
				unsigned short dstPort,
				unsigned int protocol,
				int action);

	virtual ~CFireWallDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFireWallDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIREWALLDOC_H__99012AD6_A25C_427D_94EC_AA34F9FA9E93__INCLUDED_)

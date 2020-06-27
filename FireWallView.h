// FireWallView.h : interface of the CFireWallView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREWALLVIEW_H__BABAE61A_96BA_412B_9F17_0B3F8858EAAD__INCLUDED_)
#define AFX_FIREWALLVIEW_H__BABAE61A_96BA_412B_9F17_0B3F8858EAAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFireWallView : public CFormView
{
protected: // create from serialization only
	CFireWallView();
	DECLARE_DYNCREATE(CFireWallView)

public:
	//{{AFX_DATA(CFireWallView)
	enum{ IDD = IDD_FIREWALL_FORM };
	CListCtrl	m_rules;	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CFireWallDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFireWallView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateList();
	virtual ~CFireWallView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void AddRuleToList(unsigned long srcIp, 
					   unsigned long srcMask,
					   unsigned short srcPort, 
					   unsigned long dstIp, 
					   unsigned long dstMask,
					   unsigned short dstPort, 
					   unsigned int protocol, 
					   int action);

	//{{AFX_MSG(CFireWallView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FireWallView.cpp
inline CFireWallDoc* CFireWallView::GetDocument()
   { return (CFireWallDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIREWALLVIEW_H__BABAE61A_96BA_412B_9F17_0B3F8858EAAD__INCLUDED_)

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B6ACFF44_C872_4A75_8241_AC820BB6A5DC__INCLUDED_)
#define AFX_MAINFRM_H__B6ACFF44_C872_4A75_8241_AC820BB6A5DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "winioctl.h"
#include "TDriver.h"
#include "DrvFltIp.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	BOOL Installed;   //规则安装标志，TRUE-已安装；FALSE-未安装
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	BOOL started;  //开始过滤标志，TRUE-已开始；FALSE-未开始
	TDriver filterDriver;  //
	TDriver ipFltDrv;   //

// Generated message map functions
protected:	

	BOOL AddFilterToFw(unsigned long srcIp, 
					   unsigned long srcMask,
					   unsigned short srcPort, 
					   unsigned long dstIp,
					   unsigned long dstMask,
					   unsigned short dstPort,
					   unsigned int protol,
					   int action);

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAppExit();
	afx_msg void OnButtonadd();
	afx_msg void OnButtondel();
	afx_msg void OnButtonstart();
	afx_msg void OnButtonstop();
	afx_msg void OnButtonuninstall();
	afx_msg void OnMenuAddRule();
	afx_msg void OnMenuDelRule();
	afx_msg void OnMenuInstallRules();
	afx_msg void OnMenuStart();
	afx_msg void OnMenuStop();
	afx_msg void OnMenuSaveRules();
	afx_msg void OnMenuUninstallRules();
	afx_msg void OnMenuLoadRules();
	afx_msg void OnUpdateButtonStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuStop(CCmdUI* pCmdUI);
	afx_msg void OnButtonInstall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B6ACFF44_C872_4A75_8241_AC820BB6A5DC__INCLUDED_)


// DiplomaView.h : interface of the CDiplomaView class
//

#pragma once

#include "DiplomaDoc.h"

class CDiploma2DView : public CView
{
protected: // create from serialization only
	CDiploma2DView();
	DECLARE_DYNCREATE(CDiploma2DView)

// Attributes
public:
	CDiplomaDoc* GetDocument() const;

  void Initialize(const std::wstring& i_caption);
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CDiploma2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
  std::wstring m_caption;
};

#ifndef _DEBUG  // debug version in DiplomaView.cpp
inline CDiplomaDoc* CDiploma2DView::GetDocument() const
   { return reinterpret_cast<CDiplomaDoc*>(m_pDocument); }
#endif


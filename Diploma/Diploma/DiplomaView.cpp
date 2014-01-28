
// DiplomaView.cpp : implementation of the CDiplomaView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Diploma.h"
#endif

#include "DiplomaDoc.h"
#include "DiplomaView.h"
#include "GridRenderer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiplomaView

IMPLEMENT_DYNCREATE(CDiploma2DView, CView)

BEGIN_MESSAGE_MAP(CDiploma2DView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDiplomaView construction/destruction
//////////////////////////////////////////////////////////////////////////
CDiploma2DView::CDiploma2DView()
  {
  }

//////////////////////////////////////////////////////////////////////////
CDiploma2DView::~CDiploma2DView()
  {
  }

//////////////////////////////////////////////////////////////////////////
BOOL CDiploma2DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDiplomaView drawing
//////////////////////////////////////////////////////////////////////////
void CDiploma2DView::OnDraw(CDC* pDC)
  {
	CDiplomaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
  RenderInfo info;
  info.m_grid_caption = m_caption;
  
  CRect rc;
  GetClientRect(&rc);

  CPoint top_left(int(rc.left + rc.Width() * 0.1), int(rc.top + rc.Height() * 0.1));
  info.m_top_left = top_left;
  info.m_hieght = (int)(rc.Height() * 0.8);
  info.m_width  = (int)(rc.Width() * 0.8);

  GridRenderer grid;
  grid.RenderGrid(pDC, info);
  }

void CDiploma2DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDiploma2DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDiplomaView diagnostics

#ifdef _DEBUG
void CDiploma2DView::AssertValid() const
{
	CView::AssertValid();
}

void CDiploma2DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDiplomaDoc* CDiploma2DView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDiplomaDoc)));
	return (CDiplomaDoc*)m_pDocument;
}

//////////////////////////////////////////////////////////////////////////
void CDiploma2DView::Initialize( const std::wstring& i_caption )
  {
  m_caption = i_caption;
  }

#endif //_DEBUG


// CDiplomaView message handlers

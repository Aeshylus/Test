
// DiplomaDoc.cpp : implementation of the CDiplomaDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Diploma.h"
#endif

#include "EMouseType.h"
#include "DiplomaDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDiplomaDoc

IMPLEMENT_DYNCREATE(CDiplomaDoc, CDocument)

BEGIN_MESSAGE_MAP(CDiplomaDoc, CDocument)
END_MESSAGE_MAP()


// CDiplomaDoc construction/destruction

CDiplomaDoc::CDiplomaDoc()
  : mp_mouse(MiceFactory::CreateMouse(this, ID_SELECT_MOUSE))
  {
	// TODO: add one-time construction code here
  }

CDiplomaDoc::~CDiplomaDoc()
{
}

BOOL CDiplomaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CDiplomaDoc serialization

void CDiplomaDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CDiplomaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CDiplomaDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDiplomaDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDiplomaDoc diagnostics

#ifdef _DEBUG
void CDiplomaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDiplomaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

//////////////////////////////////////////////////////////////////////////
MiceFactory::TMouse CDiplomaDoc::GetCurrentMouse() const
  {
  return mp_mouse;
  }

//////////////////////////////////////////////////////////////////////////
void CDiplomaDoc::SetMouse( const MiceFactory::TMouse& i_mouse )
  {
  mp_mouse = i_mouse;
  }

#endif //_DEBUG


// CDiplomaDoc commands

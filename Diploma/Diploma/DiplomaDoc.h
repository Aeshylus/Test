
// DiplomaDoc.h : interface of the CDiplomaDoc class
//


#pragma once

#include "MiceFactory.h"

class CDiplomaDoc : public CDocument
{
protected: // create from serialization only
	CDiplomaDoc();
	DECLARE_DYNCREATE(CDiplomaDoc)

// Operations
public:
  MiceFactory::TMouse GetCurrentMouse() const;
  void SetMouse(const MiceFactory::TMouse& i_mouse);

	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDiplomaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
  MiceFactory::TMouse mp_mouse;
};


#pragma once

#include "DiplomaDoc.h"

#include <boost\signal.hpp>

class Camera;

class CDiploma3DView : public CView 
                     , public boost::signals::trackable
  {
  typedef CView _Super;
  typedef std::shared_ptr<Camera> TCamera;
  
  protected: 
    DECLARE_DYNCREATE(CDiploma3DView)

    // Attributes
  public:
    CDiploma3DView();

    CDiplomaDoc* GetDocument() const;

    void Intialize(const irr::core::vector3df& i_camera_pos, const irr::core::vector3df& i_camera_target);
    virtual void OnInitialUpdate() override; // called first time after construct

    // Operations
  public:

    // Overrides
  public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    
    TCamera GetCamera() const;

    void SetRotAxis(const irr::core::vector3df& i_rot_axis);

  protected:
    afx_msg void OnDestroy();

    // Implementation
  public:
    virtual ~CDiploma3DView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
  protected:
    afx_msg void OnFilePrintPreview();
    
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP()

  private:
    void _UpdateView();

  private:
    irr::IrrlichtDevice       *mp_device;
    irr::video::IVideoDriver  *mp_driver;
    irr::scene::ISceneManager *mp_smgr;
    TCamera                    mp_camera;
    irr::scene::ISceneNode*         myNode;
  };

#ifndef _DEBUG  // debug version in DiplomaView.cpp
inline CDiplomaDoc* CDiploma3DView::GetDocument() const
  { return reinterpret_cast<CDiplomaDoc*>(m_pDocument); }
#endif


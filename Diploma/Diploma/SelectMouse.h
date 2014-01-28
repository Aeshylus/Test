#pragma once

#include "IMouse.h"

class IMouseMovementLogic;

//////////////////////////////////////////////////////////////////////////
/// 
class SelectMouse : public IMouse
  {
  public:
    SelectMouse();

    virtual void OnMouseMove( CWnd* ip_wnd, UINT nFlags, CPoint point ) override;

    virtual void OnLButtonUp( CWnd* ip_wnd, UINT nFlags, CPoint point ) override;

    virtual void OnLButtonDown( CWnd* ip_wnd, UINT nFlags, CPoint point ) override;

    virtual void OnRButtonUp( CWnd* ip_wnd, UINT nFlags, CPoint point ) override;

    virtual void OnRButtonDown( CWnd* ip_wnd, UINT nFlags, CPoint point ) override;

    virtual void OnMButtonDown(CWnd* ip_wnd, UINT nFlags, CPoint point ) override;

    virtual void OnMButtonUp(CWnd* ip_wnd, UINT nFlags, CPoint point )   override;

  private:
    CPoint m_prev_point;

    std::unique_ptr<IMouseMovementLogic> mp_movement_logic;
  };

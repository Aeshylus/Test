#include "stdafx.h"

#include "SelectMouse.h"
#include "Camera.h"
#include "CDiploma3DView.h"
#include "IMouseMovementLogic.h"
#include "MiceMovementLogicFactory.h"

namespace
  {
  bool _IsWndValid(CWnd* ip_wnd)
    {
    return nullptr != dynamic_cast<CDiploma3DView*>(ip_wnd);
    }
  }

//////////////////////////////////////////////////////////////////////////
SelectMouse::SelectMouse()
  : mp_movement_logic(nullptr)
  {
  }

//////////////////////////////////////////////////////////////////////////
void SelectMouse::OnMouseMove( CWnd* ip_wnd, UINT nFlags, CPoint point )
  {
  if (mp_movement_logic)
    {
    mp_movement_logic->MakeMove(ip_wnd, m_prev_point, point);
    m_prev_point = point;
    }
  }

//////////////////////////////////////////////////////////////////////////
void SelectMouse::OnLButtonUp( CWnd* ip_wnd, UINT nFlags, CPoint point )
  {
  mp_movement_logic.reset();
  }

//////////////////////////////////////////////////////////////////////////
void SelectMouse::OnLButtonDown( CWnd* ip_wnd, UINT nFlags, CPoint point )
  {
  if (!_IsWndValid(ip_wnd))
    return;
  m_prev_point = point;
  }

//////////////////////////////////////////////////////////////////////////
void SelectMouse::OnRButtonUp( CWnd* ip_wnd, UINT nFlags, CPoint point )
  {
  mp_movement_logic.reset();
  }

//////////////////////////////////////////////////////////////////////////
void SelectMouse::OnRButtonDown( CWnd* ip_wnd, UINT nFlags, CPoint point )
  {
  if (!_IsWndValid(ip_wnd))
    return;
  m_prev_point = point;
  mp_movement_logic = CreateMovementLogic(MiceMovementType::E_TYPE_SELECT_RBUTTON);
  }

//////////////////////////////////////////////////////////////////////////
void SelectMouse::OnMButtonDown( CWnd* ip_wnd, UINT nFlags, CPoint point )
  {
  if (!_IsWndValid(ip_wnd))
    return;
  m_prev_point = point;
  mp_movement_logic = CreateMovementLogic(MiceMovementType::E_TYPE_SELECT_MBUTTON);
  }

//////////////////////////////////////////////////////////////////////////
void SelectMouse::OnMButtonUp( CWnd* ip_wnd, UINT nFlags, CPoint point )
  {
  mp_movement_logic.reset();
  }

//////////////////////////////////////////////////////////////////////////
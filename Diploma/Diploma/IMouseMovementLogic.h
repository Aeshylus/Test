#pragma once

//////////////////////////////////////////////////////////////////////////
class IMouseMovementLogic
  {
  public:
    virtual void MakeMove(CWnd* i_wnd, CPoint i_start, CPoint i_end) = 0;
  };
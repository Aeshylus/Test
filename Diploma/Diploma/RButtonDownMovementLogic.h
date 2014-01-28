#pragma once

#include "IMouseMovementLogic.h"

//////////////////////////////////////////////////////////////////////////
class RButtonDownMovementLogic : public IMouseMovementLogic
  {
  public:
    virtual void MakeMove(CWnd* i_wnd, CPoint i_start, CPoint i_end ) override;
  };
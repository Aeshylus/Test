#include "stdafx.h"

#include "MButtonDownMovementLogic.h"
#include "CDiploma3DView.h"
#include "Camera.h"

using namespace irr::core;

//////////////////////////////////////////////////////////////////////////
void MButtonDownMovementLogic::MakeMove( CWnd* i_wnd, CPoint i_start, CPoint i_end )
  {
  CDiploma3DView* p_3d_view = dynamic_cast<CDiploma3DView*>(i_wnd);
  if (!p_3d_view)
    return;

  auto camera = p_3d_view->GetCamera();
  if (!camera)
    return;

  vector3df delta = camera->ScreenToCameraCoordinates(i_end) - camera->ScreenToCameraCoordinates(i_start);
  camera->SetTarget(camera->GetTarget() + delta);
  camera->SetPosition(camera->GetPosition() + delta);
  }

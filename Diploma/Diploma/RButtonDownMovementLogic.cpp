#include "stdafx.h"

#include "RButtonDownMovementLogic.h"
#include "CDiploma3DView.h"
#include "Camera.h"

namespace
  {
  const irr::core::vector3df Oz(0., 0., 1.);

  irr::core::vector3df _CalculateRotAxis(const irr::core::vector3df& i_start, const irr::core::vector3df& i_end )
    {
    irr::core::vector3df direction = i_end - i_start;
    direction.normalize();
    auto norm  = direction.crossProduct(Oz);
    return norm.crossProduct(direction);
    }
  }

//////////////////////////////////////////////////////////////////////////
void RButtonDownMovementLogic::MakeMove(CWnd* i_wnd, CPoint i_start, CPoint i_end )
  {
  CDiploma3DView* p_3d_view = dynamic_cast<CDiploma3DView*>(i_wnd);
  if (!p_3d_view)
    return;

  auto camera = p_3d_view->GetCamera();
  if (!camera)
    return;
  
  auto start = camera->ScreenToCameraCoordinates(i_start);
  auto end = camera->ScreenToCameraCoordinates(i_end);

  irr::core::vector3df axis = _CalculateRotAxis(start, end);
  
  float angle = irr::core::vector3df(float(i_end.x - i_start.x), float(i_end.y - i_start.y), 0.).getLength();
  camera->SetRotation(angle, axis);
  }

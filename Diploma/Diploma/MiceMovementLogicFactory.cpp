#include "stdafx.h"

#include "MiceMovementLogicFactory.h"
#include "RButtonDownMovementLogic.h"
#include "MButtonDownMovementLogic.h"

//////////////////////////////////////////////////////////////////////////
std::unique_ptr<IMouseMovementLogic> CreateMovementLogic( MiceMovementType::EMovementType i_type )
  {
  switch(i_type)
    {
  case MiceMovementType::E_TYPE_SELECT_RBUTTON:
    return std::unique_ptr<IMouseMovementLogic>(new RButtonDownMovementLogic);
  case MiceMovementType::E_TYPE_SELECT_MBUTTON:
    return std::unique_ptr<IMouseMovementLogic>(new MButtonDownMovementLogic);
  default:
    ASSERT(0);
    return nullptr;
    }
  }

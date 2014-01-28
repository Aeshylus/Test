#pragma once

class IMouseMovementLogic;

//////////////////////////////////////////////////////////////////////////
///
namespace MiceMovementType
  {
  enum EMovementType
    {
    E_TYPE_SELECT_RBUTTON,
    E_TYPE_SELECT_MBUTTON
    };
  }

std::unique_ptr<IMouseMovementLogic> CreateMovementLogic(MiceMovementType::EMovementType i_type);
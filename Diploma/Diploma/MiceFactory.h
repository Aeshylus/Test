#pragma  once

#include "EMouseType.h"

class CDiplomaDoc;
class IMouse;

//////////////////////////////////////////////////////////////////////////
///
class MiceFactory
  {
  public:
    typedef std::shared_ptr<IMouse> TMouse;
    static TMouse CreateMouse(CDiplomaDoc* ip_doc, EMouseType i_type);
  };
#include "stdafx.h"

#include "MiceFactory.h"
#include "DiplomaDoc.h"
#include "SelectMouse.h"


#include <boost\function.hpp>
#include <boost\assign.hpp>

//////////////////////////////////////////////////////////////////////////
namespace
  {
  MiceFactory::TMouse _GetMouseInstance(CDiplomaDoc* ip_doc, EMouseType i_type)
    {
    static std::map<EMouseType, boost::function<MiceFactory::TMouse (void)>> creators = boost::assign::map_list_of
      (ID_SELECT_MOUSE, []()->MiceFactory::TMouse {return std::shared_ptr<SelectMouse>(new SelectMouse);});
    
    return creators[i_type]();
    }
  }

//////////////////////////////////////////////////////////////////////////
MiceFactory::TMouse MiceFactory::CreateMouse( CDiplomaDoc* ip_doc, EMouseType i_type )
  {
  return _GetMouseInstance(ip_doc, i_type);
  }

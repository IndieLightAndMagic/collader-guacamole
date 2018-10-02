#ifndef __IDNAME_H__
#define __IDNAME_H__

#include "tinyxml2/tinyxml2.h"

#include <cassert>
#include <iostream>



namespace GTech {

	struct IdName {
        std::string id;
        std::string name;
        
        virtual void SetIdName(const tinyxml2::XMLAttribute *pa);
        
    };
    
}

#endif
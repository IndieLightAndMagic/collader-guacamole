#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <string>

#include "idname.h"

namespace GTech{

    struct Material : public GTech::IdName {

        std::string     effectUrl{};

    };

}

#endif
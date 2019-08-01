#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <string>

#include "idname.h"

namespace QQE{

    struct Material : public QQE::IdName {

        std::string     effectUrl{};

    };

}

#endif
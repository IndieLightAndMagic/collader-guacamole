#ifndef __NEWPARAM_H__
#define __NEWPARAM_H__

#include "idname.h"
#include <glm/ext.hpp>

namespace QQE {

    struct NewParam : public QQE::IdName {
        enum class ParamType {
            SURFACE,
            SAMPLER2D
        };    
        ParamType paramType;
        virtual void SetIdName(const tinyxml2::XMLAttribute* pa) override;
    };
    using NewParamPtr = std::shared_ptr<NewParam>;
    
    struct Surface  : public QQE::NewParam {

        std::string init_from{};
        glm::ivec4  format{glm::ivec4(0,0,0,0)};
    
    };
    
    struct Sampler2D : public QQE::NewParam {

        std::string source{};


    };
}



#endif

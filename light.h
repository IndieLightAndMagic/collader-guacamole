#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "glm/glm.hpp"

#include "idname.h"

namespace QQE {

    struct Light : public QQE::IdName {

        enum class LightType {POINT, SPOT, SUN};
        float constant_attenuation{0.0f};
        float linear_attenuaton{0.0f};
        float quadratic_attenuation{0.0f};

        glm::vec3 color{1.0f, 0.0f, 0.0f};
        LightType lightType{QQE::Light::LightType::POINT};
        
    };

}

#endif
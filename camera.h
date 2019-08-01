#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "glm/glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <string>
#include <iostream>

#include "idname.h"

namespace QQE {

	struct Camera : public QQE::IdName {
        
        enum class ProjectionType {ORTO, PERS};
        union {
            float xmag;
            float yfov;
        }projection;
        float aspect_ratio{};
        float znear{0.1f};
        float zfar{100.0f};
        ProjectionType projectionType{ProjectionType::PERS};
        
        void Print(std::string tab = std::string{'\t'});
        
    };

}
#endif
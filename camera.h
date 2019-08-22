#ifndef __CAMERA_H__
#define __CAMERA_H__

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
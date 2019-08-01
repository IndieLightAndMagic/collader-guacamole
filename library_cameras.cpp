//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

std::shared_ptr<QQE::Camera> pCameraTmp = nullptr;

bool QQE::ColladaVisitor::VisitEnter_library_cameras(const XMLElement& e, const XMLAttribute* pa){

    auto eName          = std::string {e.Name()};
    auto pText          = GetElementText(e);
    auto pTextString    = std::stringstream{pText};
    
    if (eName == "camera"){

        pCameraTmp                          = CreateElement<QQE::Camera>(pa);
        aScene->cameras[pCameraTmp->name]    = pCameraTmp; 

    } else if (eName == "yfov") {

        pTextString >> pCameraTmp->projection.yfov; 
    
    } else if (eName == "xmag") {

        pTextString >> pCameraTmp->projection.xmag;

    } else if (eName == "ortographic" || eName == "perspective") {

        pCameraTmp->projectionType = (eName == "ortographic") ? QQE::Camera::ProjectionType::ORTO : QQE::Camera::ProjectionType::PERS;

    } else if (eName == "aspect_ratio") {

        pTextString >> pCameraTmp->aspect_ratio;

    } else if (eName == "znear") {

        pTextString >> pCameraTmp->znear;

    } else if (eName == "zfar") {

        pTextString >> pCameraTmp->zfar;

    }

    return true;

}        

bool QQE::ColladaVisitor::VisitExit_library_cameras(const XMLElement& e){

    return true;

}
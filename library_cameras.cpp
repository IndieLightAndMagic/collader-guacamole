//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

QQE::Camera* rpCameraTmp = nullptr;

bool QQE::ColladaVisitor::VisitEnter_library_cameras(const XMLElement& e, const XMLAttribute* pa){

    auto eName          = std::string {e.Name()};
    auto pText          = GetElementText(e);
    auto pTextString    = std::stringstream{pText};
    
    if (eName == "camera"){


        auto cameraNameString = std::string{pa->Next()->Value()};
        auto sp = std::make_shared<QQE::Camera>();
        rpCameraTmp = sp.get();
        auto rp = reinterpret_cast<void*>(rpCameraTmp);
        auto rpName = std::string{pa->Value()};
        aScene->cameras[cameraNameString] = sp;
        sp->id = rpName;
        sp->name = cameraNameString;
        auto id_name = std::make_pair(rpName.data(),rp);
        aScene->urlPtrMap.insert(id_name);



    } else if (eName == "yfov") {

        pTextString >> rpCameraTmp->projection.yfov;
    
    } else if (eName == "xmag") {

        pTextString >> rpCameraTmp->projection.xmag;

    } else if (eName == "ortographic" || eName == "perspective") {

        rpCameraTmp->projectionType = (eName == "ortographic") ? QQE::Camera::ProjectionType::ORTO : QQE::Camera::ProjectionType::PERS;

    } else if (eName == "aspect_ratio") {

        pTextString >> rpCameraTmp->aspect_ratio;

    } else if (eName == "znear") {

        pTextString >> rpCameraTmp->znear;

    } else if (eName == "zfar") {

        pTextString >> rpCameraTmp->zfar;

    }

    return true;

}        

bool QQE::ColladaVisitor::VisitExit_library_cameras(const XMLElement& e){

    return true;

}
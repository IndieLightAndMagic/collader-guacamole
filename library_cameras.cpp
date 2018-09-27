//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;


extern GTech::Scene aScene;
extern GTech::Camera aCamera;


bool GTech::ColladaVisitor::VisitEnter_library_cameras(const XMLElement& e, const XMLAttribute* pa){

    auto eName          = std::string {e.Name()};
    auto pText          = GetElementText(e);
    auto pTextString    = std::stringstream{pText};
    
    if (eName == "camera"){

        aCamera = GTech::Camera{};
        aCamera.SetIdName(pa);

    } else if (eName == "yfov") {

        pTextString >> aCamera.projection.yfov; 
    
    } else if (eName == "xmag") {

        pTextString >> aCamera.projection.xmag;

    } else if (eName == "ortographic" || eName == "perspective") {

        aCamera.projectionType = (eName == "ortographic") ? GTech::Camera::ProjectionType::ORTO : GTech::Camera::ProjectionType::PERS;

    } else if (eName == "aspect_ratio") {

        pTextString >> aCamera.aspect_ratio;

    } else if (eName == "znear") {

        pTextString >> aCamera.znear;

    } else if (eName == "zfar") {

        pTextString >> aCamera.zfar;

    }

    return true;

}        

bool GTech::ColladaVisitor::VisitExit_library_cameras(const XMLElement& e){

    auto eName = std::string{e.Name()};
    
    if (eName == "camera") {
        
        aScene.cameras[aCamera.name]    = aCamera;
        nodePtrMap[aCamera.id]          = &aScene.cameras[aCamera.name];           
    }

    return true;
}
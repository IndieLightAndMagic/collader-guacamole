//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;


extern GTech::Scene aScene;
extern GTech::Camera aCamera;


bool GTech::ColladaVisitor::VisitEnter_library_cameras(const XMLElement& e, const XMLAttribute* pa){

    auto eName          = std::string {e.Name()};
    auto pTextString    = std::stringstream{std::string{e.GetText()}};
    
    if (eName == "camera"){

        aCamera = GTech::Camera{};
        aCamera.SetIdName(pa);

    } else if (eName == "yfov") {

        std::stringstream{std::string{e.GetText()}} >> aCamera.projection.yfov; 
    
    } else if (eName == "xmag") {

        std::stringstream{std::string{e.GetText()}} >> aCamera.projection.xmag;

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
        
        aScene.cameras[aCamera.name] = aCamera;

    }

    return true;
}
//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

std::shared_ptr<GTech::Light> pLightTmp = nullptr;

bool GTech::ColladaVisitor::VisitExit_library_lights(const tinyxml2::XMLElement &e){

    return true;
}

bool GTech::ColladaVisitor::VisitEnter_library_lights(const tinyxml2::XMLElement &e, const tinyxml2::XMLAttribute *pa){

    auto eName = std::string{e.Name()};
    auto attrMap = GetAttrMap(pa);
    auto textString = std::stringstream{GetElementText(e)};

    if (eName == "light"){

        pLightTmp                       = CreateElement<GTech::Light>(pa);
        aScene.lights[pLightTmp->name]  = pLightTmp;

    } else if (eName == "color") {

        textString >> pLightTmp->color.r;
        textString >> pLightTmp->color.g;
        textString >> pLightTmp->color.b;

    } else if (eName == "linear_attenuation") {

        textString >> pLightTmp->linear_attenuaton;

    }
    
    return true;
}
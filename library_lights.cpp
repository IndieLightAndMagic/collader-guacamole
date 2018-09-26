//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;




extern GTech::Scene aScene;
extern GTech::Light aLight;



bool GTech::ColladaVisitor::VisitExit_library_lights(const tinyxml2::XMLElement &e){

    auto eName = std::string{e.Name()};

    if (eName == "light"){

        aScene.lights[aLight.name]  = aLight;
        nodePtrMap[aLight.id]       = &aScene.lights[aLight.name];

    } 
    return true;
}

bool GTech::ColladaVisitor::VisitEnter_library_lights(const tinyxml2::XMLElement &e, const tinyxml2::XMLAttribute *pa){

    auto eName = std::string{e.Name()};
    auto attrMap = GetAttrMap(pa);
    auto textString = std::stringstream{GetElementText(e)};

    if (eName == "light"){

        aLight = GTech::Light{};
        aLight.SetIdName(pa);

    } else if (eName == "color") {

        textString >> aLight.color.r;
        textString >> aLight.color.g;
        textString >> aLight.color.b;

    } else if (eName == "linear_attenuation") {

        textString >> aLight.linear_attenuaton;

    }
    
    return true;
}
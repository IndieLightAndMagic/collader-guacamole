//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

extern GTech::Scene     aScene;
extern GTech::Material  aMaterial;


bool GTech::ColladaVisitor::VisitExit_library_materials(const tinyxml2::XMLElement& e){

    auto eName = std::string{e.Name()};

    if (eName == "material") {

        aScene.materials[aMaterial.name]    = aMaterial;
        nodePtrMap[aMaterial.id]            = &aScene.materials[aMaterial.name];

    }
    return true;
}
bool GTech::ColladaVisitor::VisitEnter_library_materials(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa){

    auto eName = std::string{e.Name()};

    if( eName == "material"){

        aMaterial = GTech::Material{};
        aMaterial.SetIdName(pa);

    } else if (eName == "instance_effect") {

        auto attrMap = GetAttrMap(pa);
        auto pUrlValue = attrMap["url"].c_str();
        pUrlValue++;

        auto urlValue = std::string{pUrlValue};
        if (nodePtrMap.find(urlValue) != nodePtrMap.end()) aMaterial.pShader = dynamic_cast<GTech::Effect*>(nodePtrMap[urlValue]);
        else aMaterial.pShader = nullptr;

    }

    return true;
}


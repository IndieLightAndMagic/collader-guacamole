//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

bool GTech::ColladaVisitor::VisitExit_library_materials(const tinyxml2::XMLElement& e){

    auto eName = std::string{e.Name()};

    if (eName == "material") {

        aScene.materials[aMaterial.name]    = aMaterial;
        aScene.nodePtrMap[aMaterial.id]     = &aScene.materials[aMaterial.name];

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
        auto pUrlValue = attrMap["url"].c_str() + 1;
        aMaterial.effectUrl = std::string{pUrlValue};

    }

    return true;
}


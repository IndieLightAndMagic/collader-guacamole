//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

std::shared_ptr<QQE::Material> pMaterialTmp = nullptr;

bool QQE::ColladaVisitor::VisitExit_library_materials(const tinyxml2::XMLElement& e){

    return true;
}
bool QQE::ColladaVisitor::VisitEnter_library_materials(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa){

    auto eName = std::string{e.Name()};

    if( eName == "material"){

        pMaterialTmp                            = CreateElement<QQE::Material>(pa);
        aScene->materials[pMaterialTmp->name]    = pMaterialTmp;

    } else if (eName == "instance_effect") {

        auto attrMap = GetAttrMap(pa);
        auto pUrlValue = attrMap["url"].c_str() + 1;
        pMaterialTmp->effectUrl = std::string{pUrlValue};



    }

    return true;
}


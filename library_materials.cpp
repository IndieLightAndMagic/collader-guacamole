//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


QSharedPointer<QQE::Material> pMaterialTmp = nullptr;

bool QQE::ColladaVisitor::VisitExit_library_materials(const QDomElement& e){

    return true;
}
bool QQE::ColladaVisitor::VisitEnter_library_materials(const QDomElement& e, const QDomNamedNodeMap& pa){

    auto eName = e.nodeName();

    if( eName == "material"){

        pMaterialTmp                            = CreateElement<QQE::Material>(pa);
        aScene->materials[pMaterialTmp->name]    = pMaterialTmp;

    } else if (eName == "instance_effect") {

        auto attrMap = GetAttrMap(e);
        auto pUrlValue = attrMap["url"].toStdString().data() + 1;
        pMaterialTmp->effectUrl = std::string{pUrlValue};



    }

    return true;
}


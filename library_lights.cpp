//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"
#include <sstream>


QSharedPointer<QQE::Light> pLightTmp = nullptr;

bool QQE::ColladaVisitor::VisitExit_library_lights(const QDomElement& e){

    return true;
}

bool QQE::ColladaVisitor::VisitEnter_library_lights(const QDomElement& e, const QDomNamedNodeMap& pa){

    auto eName = e.nodeName();
    auto attrMap = GetAttrMap(e);
    auto textString = std::stringstream{GetElementText(e).toStdString()};

    if (eName == "light"){

        pLightTmp                       = CreateElement<QQE::Light>(pa);
        aScene->lights[pLightTmp->name]  = pLightTmp;

    } else if (eName == "color") {

        auto red = 0.0f;
        auto green = 0.0f;
        auto blue = 0.0f;

        textString >> red;
        pLightTmp->color.setX(red);
        textString >> green;
        pLightTmp->color.setY(green);
        textString >> blue;
        pLightTmp->color.setZ(blue);

    } else if (eName == "linear_attenuation") {

        textString >> pLightTmp->linear_attenuaton;

    }
    
    return true;
}
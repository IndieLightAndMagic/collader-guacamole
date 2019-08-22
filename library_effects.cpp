//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"
#include <sstream>


QSharedPointer<QQE::Effect> pShaderTmp = nullptr;
bool QQE::ColladaVisitor::VisitExit_library_effects(const QDomElement& e){
    
    return true;

}
bool QQE::ColladaVisitor::VisitEnter_library_effects(const QDomElement& e, const QDomNamedNodeMap& pa){

    auto eName      = e.nodeName();
    auto parentName = GetParentName(e);
    auto eText      = e.text();

    if (eName == "effect") {

        pShaderTmp                          = CreateElement<QQE::Effect>(pa);
        aScene->shaders[pShaderTmp->name]    = pShaderTmp; 
        
    } else if (eName == "float") {

        float property;
        std::stringstream{std::string{eText.toStdString()}} >> property;

        if (parentName == "shininess"){

            pShaderTmp->shininess = property;

        } else if (parentName == "index_of_refraction"){

            pShaderTmp->refractionIndex = property;

        }

    } else if (eName == "color") {

        auto colorVectorText    = std::stringstream{eText.toStdString()};

        auto r = 0.0f;
        auto g = 0.0f;
        auto b = 0.0f;
        auto a = 0.0f;

        colorVectorText >> r;
        colorVectorText >> g;
        colorVectorText >> b;
        colorVectorText >> a;

        auto colorVector = QVector4D(r,g,b,a);


        if (parentName == "emission") {

            pShaderTmp->emission = colorVector;

        } else if (parentName == "diffuse") {

            pShaderTmp->diffuse = colorVector;

        } else if (parentName == "ambient") {

            pShaderTmp->ambient = colorVector;

        } else if (parentName =="specular") {

            pShaderTmp->specular = colorVector;

        } else if (parentName == "reflective") {

            pShaderTmp->reflective = colorVector;

        } 


    } else if (eName == "source"){
        

    } else if (eName == "texture") {

        auto attrMap = GetAttrMap(e);
        pShaderTmp->textureUrl = attrMap["texture"].toStdString();
    
    } else if (pShaderTmp->shadertypemap.find(eName) != pShaderTmp->shadertypemap.end()) {

        pShaderTmp->shaderType = pShaderTmp->shadertypemap[eName];

    }

    return true;
}

//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;


std::shared_ptr<GTech::Effect> pShaderTmp = nullptr;
bool GTech::ColladaVisitor::VisitExit_library_effects(const XMLElement& e){
    
    return true;

}
bool GTech::ColladaVisitor::VisitEnter_library_effects(const XMLElement& e, const XMLAttribute* pa){

    auto eName      = std::string{e.Name()};
    auto parentName = GetParentName(e);
    auto eText      = e.GetText();

    if (eName == "effect") {

        pShaderTmp                          = CreateElement<GTech::Effect>(pa);
        aScene->shaders[pShaderTmp->name]    = pShaderTmp; 
        
    } else if (eName == "float") {

        float property;
        std::stringstream{std::string{eText}} >> property;

        if (parentName == "shininess"){

            pShaderTmp->shininess = property;

        } else if (parentName == "index_of_refraction"){

            pShaderTmp->refractionIndex = property;

        }

    } else if (eName == "color") {

        auto colorVectorText    = std::stringstream{std::string{eText}};
        auto colorVector        = glm::vec4{};

        colorVectorText >> colorVector.r;
        colorVectorText >> colorVector.g;
        colorVectorText >> colorVector.b;
        colorVectorText >> colorVector.a;

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

        auto attrMap = GetAttrMap(pa);
        pShaderTmp->textureUrl = std::string{attrMap["texture"]};
    
    } else if (pShaderTmp->shadertypemap.find(eName) != pShaderTmp->shadertypemap.end()) {

        pShaderTmp->shaderType = pShaderTmp->shadertypemap[eName];

    }

    return true;
}

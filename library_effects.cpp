//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

bool GTech::ColladaVisitor::VisitExit_library_effects(const XMLElement& e){

    auto eName = std::string{e.Name()};

    if (eName == "effect") {

        aScene.shaders[aShader.name]    = aShader;
        aScene.nodePtrMap[aShader.id]   = &aScene.shaders[aShader.name];

    } 
    return true;

}
bool GTech::ColladaVisitor::VisitEnter_library_effects(const XMLElement& e, const XMLAttribute* pa){

    auto eName      = std::string{e.Name()};
    auto parentName = GetParentName(e);
    auto eText      = e.GetText();

    if (eName == "effect") {

        aShader = GTech::Effect{};
        aShader.SetIdName(pa);
        
    } else if (eName == "float") {

        float property;
        std::stringstream{std::string{eText}} >> property;

        if (parentName == "shininess"){

            aShader.shininess = property;

        } else if (parentName == "index_of_refraction"){

            aShader.refractionIndex = property;

        }

    } else if (eName == "color") {

        auto colorVectorText    = std::stringstream{std::string{eText}};
        auto colorVector        = glm::vec4{};

        colorVectorText >> colorVector.r;
        colorVectorText >> colorVector.g;
        colorVectorText >> colorVector.b;
        colorVectorText >> colorVector.a;

        if (parentName == "emission") {

            aShader.emission = colorVector;

        } else if (parentName == "diffuse") {

            aShader.diffuse = colorVector;

        } else if (parentName == "ambient") {

            aShader.ambient = colorVector;

        } else if (parentName =="specular") {

            aShader.specular = colorVector;

        } else if (parentName == "reflective") {

            aShader.reflective = colorVector;

        }


    } else if (aShader.shadertypemap.find(eName) != aShader.shadertypemap.end()) {

        aShader.shaderType = aShader.shadertypemap[eName];

    }

    return true;
}

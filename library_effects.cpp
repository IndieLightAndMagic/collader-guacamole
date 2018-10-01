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

        auto ptr = aShader.floatpropertiesmap[parentName];
        std::stringstream{std::string{eText}} >> *ptr;

    } else if (eName == "color") {

        auto ptr = aShader.colorpropertiesmap[parentName];
        auto colorVectorText = std::stringstream{std::string{eText}};
        colorVectorText >> ptr->r;
        colorVectorText >> ptr->g;
        colorVectorText >> ptr->b;
        colorVectorText >> ptr->a;

    } else if (aShader.shadertypemap.find(eName) != aShader.shadertypemap.end()) {

        aShader.shaderType = aShader.shadertypemap[eName];

    }

    return true;
}

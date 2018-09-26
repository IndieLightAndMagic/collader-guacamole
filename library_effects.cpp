//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;



extern GTech::Scene     aScene;
extern GTech::Effect    aShader;

bool GTech::ColladaVisitor::VisitExit_library_effects(const XMLElement& e){

    auto eName = std::string{e.Name()};

    if (eName == "effect") {

        aScene.shaders[aShader.name]    = aShader;
        nodePtrMap[aShader.id]          = &aScene.shaders[aShader.name];

    } 
    return true;

}
bool GTech::ColladaVisitor::VisitEnter_library_effects(const XMLElement& e, const XMLAttribute* pa){

    auto eName = std::string{e.Name()};
    auto shadertypemap = std::map<std::string, GTech::Effect::ShaderType>{
        std::make_pair("blinn", GTech::Effect::ShaderType::BLINN),
        std::make_pair("phong", GTech::Effect::ShaderType::PHONG),
        std::make_pair("lambert", GTech::Effect::ShaderType::LAMBERT),
        std::make_pair("constant", GTech::Effect::ShaderType::CONSTANT)
    };
    auto v4propertiesmap = std::map<std::string, glm::vec4*>{
        std::make_pair("emission", &aShader.emission),
        std::make_pair("ambient", &aShader.ambient),
        std::make_pair("diffuse", &aShader.diffuse),
        std::make_pair("specular", &aShader.specular),
        std::make_pair("reflective", &aShader.reflective)
    };
    auto floatpropertiesmap = std::map<std::string, float*>{
        std::make_pair("shininess", &aShader.shininess),
        std::make_pair("index_of_refraction", &aShader.refractionIndex),
    };
    if (eName == "effect") {

        aShader = GTech::Effect{};
        aShader.SetIdName(pa);
        
    } else if (shadertypemap.find(eName) != shadertypemap.end()) {

        aShader.shaderType = shadertypemap[eName];

    } else if (v4propertiesmap.find(eName) != v4propertiesmap.end()) {

        tmpv4ptr = v4propertiesmap[eName];

    } else if (floatpropertiesmap.find(eName) != floatpropertiesmap.end()) {

        tmpfloatptr = floatpropertiesmap[eName];

    } else if (eName == "color") {

        auto colorText = std::stringstream{GetElementText(e)};
        auto setRGBColor = [&](auto rgbVector){

            colorText >> rgbVector->r;
            colorText >> rgbVector->g;
            colorText >> rgbVector->b;

            return;
        };
        auto setRGBAColor = [&](auto rgbaVector){

            setRGBColor(rgbaVector);
            colorText >> rgbaVector->a;

        };

        setRGBAColor(tmpv4ptr);


    } else if (eName == "float") {

        auto floatText = std::stringstream{GetElementText(e)};
        floatText >> *tmpfloatptr;
        
    } else if (eName == "init_from") {

        aShader.imageId = GetElementText(e);

    }

    return true;
}

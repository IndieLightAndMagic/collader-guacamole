//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;




GTech::Mesh aMesh;
GTech::Scene aScene;
GTech::Light aLight;
GTech::Image anImage;
GTech::Camera aCamera;
GTech::Shader aShader;
GTech::Material aMaterial;

using AttrMap = std::map<std::string, std::string>;

AttrMap GetAttrMap (const tinyxml2::XMLAttribute* pa){

    auto attrMap = AttrMap{}; 
    for (;pa; pa = pa->Next()){
        attrMap[std::string{pa->Name()}] = std::string{pa->Value()};
    }
    return attrMap;
}

bool GTech::ColladaVisitor::VisitEnter_library_geometries(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa){

    auto eName = std::string{e.Name()};

    if (eName == "geometry") {

        aMesh = GTech::Mesh{};
        aMesh.SetIdName(pa);

    } else if (eName == "float_array") {

        //Get Attr dict
        auto attrMap = GetAttrMap(pa);

        //Get Parent dict
        auto ppa = reinterpret_cast<const XMLElement*>(e.Parent())->FirstAttribute();
        auto attrMapParent = GetAttrMap(ppa);

        //Get id
        auto id = attrMapParent["id"];

        //Calc the current vector size
        auto floatVectorSize = aMesh.floatVector.size();
        aMesh.offsetMap[id] = floatVectorSize;

        //Read additional floats
        auto countString    = std::stringstream{attrMap["count"]};
        unsigned int count{0};
        countString >> count;

        //Resize Vector
        aMesh.floatVector.resize(floatVectorSize + count);
        aMesh.sizeMap[id] = count;
        auto newSize = aMesh.floatVector.size();

        //Parse the floats
        auto theFloats = std::stringstream{e.GetText()};
        auto floatData = aMesh.floatVector.data();
        for (auto index = floatVectorSize; index < newSize; index++){

            theFloats >> aMesh.floatVector[index];

        }

    } else if (eName == "input") {

        const auto p = reinterpret_cast<const XMLElement*>(e.Parent());
        auto ppa = p->FirstAttribute();
        auto pName = std::string{p->Name()};

        auto attrMap = GetAttrMap(pa);
        auto attrMapParent = GetAttrMap(ppa);

        auto pSource = attrMap["source"].c_str();
        auto source  = std::string{++pSource};

        if (pName == "vertices") {
        
            auto aliasId = attrMapParent["id"];
            aMesh.sizeMap[aliasId] = aMesh.sizeMap[source];
            aMesh.offsetMap[aliasId] = aMesh.offsetMap[source];
        
        } else if (pName == "triangles") {

            auto triangleArrayIndex     = aMesh.triangleArray.size();
            auto& triangles             = aMesh.triangleArray[triangleArrayIndex];
            
            auto inputDataConfig        = GTech::InputDataConfig{};

            auto semantic               = attrMap["semantic"];
            if ( semantic == "TEXCOORD" )       inputDataConfig.dataType = GTech::InputDataConfig::DataType::TEXCOORDS;
            else if ( semantic == "NORMAL" )    inputDataConfig.dataType = GTech::InputDataConfig::DataType::NORMALS;
            else if ( semantic == "VERTICES" )  inputDataConfig.dataType = GTech::InputDataConfig::DataType::VERTICES;  
            
            auto pSourceId              = attrMap["source"].c_str();
            inputDataConfig.sourceId    = std::string{++pSourceId};

            auto offsetString           = std::stringstream{attrMap["offset"]};
            offsetString >> inputDataConfig.offset;

        } 

    } else if (eName == "triangles") {

        auto attrMap            = GetAttrMap(pa);
        auto triangles          = GTech::TriangleArray{};
        
        auto countString        = std::stringstream{attrMap["count"]};
        countString >> triangles.count;

        triangles.materialId    = attrMap["material"];
        aMesh.triangleArray.push_back(triangles);

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
        if (nodePtrMap.find(urlValue) != nodePtrMap.end()) aMaterial.pShader = dynamic_cast<GTech::Shader*>(nodePtrMap[urlValue]);
        else aMaterial.pShader = nullptr;
    }

    return true;
}

bool GTech::ColladaVisitor::VisitEnter_library_images(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa){
    
    auto eName = std::string{e.Name()};

    if( eName == "image"){
        anImage = GTech::Image{};
        anImage.SetIdName(pa);

    } else if (eName == "init_from") {

        anImage.path = std::string{e.GetText()};
    }

    return true;
}
        
bool GTech::ColladaVisitor::VisitEnter_library_effects(const XMLElement& e, const XMLAttribute* pa){

    auto eName = std::string{e.Name()};
    auto shadertypemap = std::map<std::string, GTech::Shader::ShaderType>{
        std::make_pair("blinn", GTech::Shader::ShaderType::BLINN),
        std::make_pair("phong", GTech::Shader::ShaderType::PHONG),
        std::make_pair("lambert", GTech::Shader::ShaderType::LAMBERT),
        std::make_pair("constant", GTech::Shader::ShaderType::CONSTANT)
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

        aShader = GTech::Shader{};
        aShader.SetIdName(pa);
        
    } else if (shadertypemap.find(eName) != shadertypemap.end()) {

        aShader.shaderType = shadertypemap[eName];

    } else if (v4propertiesmap.find(eName) != v4propertiesmap.end()) {

        tmpv4ptr = v4propertiesmap[eName];

    } else if (floatpropertiesmap.find(eName) != floatpropertiesmap.end()) {

        tmpfloatptr = floatpropertiesmap[eName];

    } else if (eName == "color") {

        auto colorText = std::stringstream{e.GetText()};
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

        auto floatText = std::stringstream{e.GetText()};
        floatText >> *tmpfloatptr;
        
    } else if (eName == "init_from") {

        aShader.imageId = e.GetText();

    }

    return true;
}


bool GTech::ColladaVisitor::VisitEnter(const XMLElement& e, const XMLAttribute* pa){
    
    auto eName                      = std::string{e.Name()};
    auto eNameSearchForVisitorState = stateMap.find(eName);
    auto eNameStateFound            = eNameSearchForVisitorState != stateMap.end();
    

    if  ( eNameStateFound ){

        auto& visitorStateName = eName;
        visitorState = stateMap[visitorStateName];

    } else if (visitorState == ColladaVisitor::VisitorState::library_effects){

        return VisitEnter_library_effects(e, pa);

    } else if (visitorState == ColladaVisitor::VisitorState::library_images){

        return VisitEnter_library_images(e, pa);

    } else if (visitorState == ColladaVisitor::VisitorState::library_materials){

        return VisitEnter_library_materials(e, pa);

    } else if (visitorState == ColladaVisitor::VisitorState::library_geometries){

        return VisitEnter_library_geometries(e, pa);

    } else if (eName == "authoring_tool") {

        aScene.authoring_tool = e.GetText();

    } else if (eName == "up_axis") {

        auto z_up = std::string{e.GetText()};
        aScene.z_up = z_up == "Z_UP" ? true : false;

    } else if (eName == "perspective") {

        aCamera.x.fov = 49.13434f;
        aCamera.projectionType = GTech::Camera::ProjectionType::PERS;

    } else if (eName == "ortographic") {

        aCamera.x.mag = 3.657143f;
        aCamera.projectionType = GTech::Camera::ProjectionType::ORTO;

    } else if (eName == "znear") {

        e.QueryFloatText(&aCamera.znear);

    } else if (eName == "zfar") {

        e.QueryFloatText(&aCamera.zfar);

    } else if (eName == "camera") {

        aCamera = GTech::Camera{};
        aCamera.SetIdName(pa);

    } else if (eName == "light") {

        aLight = GTech::Light{};
        aLight.SetIdName(pa);

    } else if (eName == "color") {

        auto colorText = std::stringstream{e.GetText()};
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
        if (visitorState == VisitorState::library_lights){

            setRGBColor(&aLight.color);

        }

    } else if (eName == "geometry") {

        aMesh = GTech::Mesh{};
        aMesh.SetIdName(pa);

    } 

    return true;
}

bool GTech::ColladaVisitor::VisitExit(const XMLElement& e){

    auto eName = std::string{e.Name()};

    if (eName == "camera"){

        aScene.cameras[aCamera.name] = aCamera;

    } else if (eName == "light"){

        aScene.lights[aLight.name] = aLight;

    } else if (eName == "image") {

        aScene.images[anImage.name] = anImage;
        nodePtrMap[anImage.id]      = &aScene.images[anImage.name];

    } else if (eName == "effect") {

        aScene.shaders[aShader.name]    = aShader;
        nodePtrMap[aShader.id]          = &aScene.shaders[aShader.name];

    } else if (eName == "material") {

        aScene.materials[aMaterial.name]    = aMaterial;
        nodePtrMap[aMaterial.id]            = &aScene.materials[aMaterial.name];

    }

    return true;
}

int main (){

	XMLDocument doc;
	doc.LoadFile("../simple.dae");

    GTech::ColladaVisitor visitor;
    auto pVisitor = &visitor;
    doc.Accept(pVisitor);

	return 0;
}
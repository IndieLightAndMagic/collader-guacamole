//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;




GTech::Scene aScene;
GTech::Camera aCamera;
GTech::Light aLight;
GTech::Material aMaterial;
GTech::Mesh aMesh;

bool GTech::ColladaVisitor::VisitEnter(const XMLElement& e, const XMLAttribute* pa){
    
    auto eName                      = std::string{e.Name()};
    auto eNameSearchForVisitorState = stateMap.find(eName);
    auto eNameStateFound            = eNameSearchForVisitorState != stateMap.end();
    
    auto eNameSearchForShaderType   = aMaterial.shaderTypeMap.find(eName);
    auto eNameShaderTypeFound       = eNameSearchForShaderType != aMaterial.shaderTypeMap.end(); 
    
    if  ( eNameStateFound ){

        auto& visitorStateName = eName;
        visitorState = stateMap[visitorStateName];

    } else if (eNameShaderTypeFound){

        aMaterial.shaderType = aMaterial.shaderTypeMap[eName];

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
        aCamera.setIdName(pa);

    } else if (eName == "light") {

        aLight = GTech::Light{};
        aLight.setIdName(pa);

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

        } else if (visitorState == VisitorState::library_effects){

            auto materialPropertyName = std::string{pa->Value()};
            std::map<std::string, glm::vec4*> propertyVectorMap {
                std::make_pair("emission", &aMaterial.emission),
                std::make_pair("ambient", &aMaterial.ambient),
                std::make_pair("diffuse", &aMaterial.diffuse),
                std::make_pair("specular", &aMaterial.specular)
            };
            setRGBAColor(propertyVectorMap[materialPropertyName]);

        }

    } else if (eName == "effect") {

        aMaterial = GTech::Material{};
        aMaterial.setIdName(pa,"-effect");
        
    } else if (eName == "geometry") {

        aMesh = GTech::Mesh{};
        aMesh.setIdName(pa);

    } else if (eName == "param") {

        aMesh.temporalStrideXYZ += pa->Value();
        
    } else if (eName == "accessor") {

        aMesh.temporalStrideXYZ = std::string{};

        auto paux = pa->Next();
        auto countStrideStream = std::stringstream{std::string{paux->Value()} + std::string{" "} + std::string{paux->Next()->Value()}};
        int count, stride; countStrideStream >> count; countStrideStream >> stride; int numelements = count * stride;

        aMesh.temporalNextIndexToWrite = aScene.geometricalData.size();
        aScene.geometricalData.resize(aMesh.temporalNextIndexToWrite + numelements);

    } else if (eName == "source"){

        std::vector<std::string> tokens {"-positions", "-normals", "-texcoords"};
        auto sourceIdString = std::string{pa->Value()};
        for (auto token : tokens){
            if (aMesh.id + token == sourceIdString) {
                if      ( token == tokens[0] )  aMesh.temporalDataType = GTech::Mesh::DataType::VERTICES;
                else if ( token == tokens[1] )  aMesh.temporalDataType = GTech::Mesh::DataType::NORMALS;
                else if ( token == tokens[2] )  aMesh.temporalDataType = GTech::Mesh::DataType::TEXCOORDS;
            }
        }

    } else if (eName == "float_array") {

        aMesh.temporalStringStream = std::stringstream{std::string{e.GetText()}};

    }

    return true;
}

bool GTech::ColladaVisitor::VisitExit(const XMLElement& e){

    auto eName = std::string{e.Name()};

    if (eName == "camera"){

        aScene.cameras[aCamera.name] = aCamera;

    } else if (eName == "light"){

        aScene.lights[aLight.name] = aLight;

    } else if (eName == "effect"){

        aScene.materials[aMaterial.name] = aMaterial;

    } else if (eName == "source"){

        auto numelements    = aScene.geometricalData.size() - aMesh.temporalNextIndexToWrite;
        auto keyPair        = std::make_pair(aMesh.temporalNextIndexToWrite, numelements);

        if (aMesh.temporalDataType == GTech::Mesh::DataType::VERTICES) {

            aMesh.vertices  = keyPair;

        } else if (aMesh.temporalDataType == GTech::Mesh::DataType::NORMALS) {

            aMesh.normals   = keyPair;

        } else if (aMesh.temporalDataType == GTech::Mesh::DataType::TEXCOORDS) {

            aMesh.texcoords = keyPair;

        }

        auto strideSize = aMesh.temporalStrideXYZ.length();
        glm::vec3 fvector;

        for (auto index = 0; index < numelements; ++index){

            auto strideIndex = index % strideSize;

            auto dimensionToken = aMesh.temporalStrideXYZ.data()[strideIndex];
            if ( dimensionToken == 'X') {
                aMesh.temporalStringStream >> fvector.x;
            } else if (dimensionToken == 'Y') {
                aMesh.temporalStringStream >> fvector.y;
            } else if (dimensionToken == 'Z') {
                aMesh.temporalStringStream >> fvector.z;
            }

            if (strideIndex == 2) {

                if (aScene.z_up) std::swap(fvector.y, fvector.z);
                auto pfloat = aScene.geometricalData.data();
                pfloat [aMesh.temporalNextIndexToWrite++] = fvector.x;
                pfloat [aMesh.temporalNextIndexToWrite++] = fvector.y;
                pfloat [aMesh.temporalNextIndexToWrite++] = fvector.z;
            }

        }

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
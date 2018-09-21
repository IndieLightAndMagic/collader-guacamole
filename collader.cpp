//http://www.wazim.com/Collada_Tutorial_1.htm

#include "tinyxml2/tinyxml2.h"
#include "glm/glm.hpp"

#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

using namespace tinyxml2;
using namespace std;


namespace GTech {


    struct IdName {
        std::string id;
        std::string name;
        glm::vec3 color;
        virtual void setIdName(const tinyxml2::XMLAttribute* pa){
            assert(pa != nullptr);
            if (pa) id = pa->Value();
            auto next = pa->Next();
            assert(next != nullptr);
            if (next) name = next->Value();
        }
    };

    struct Camera : public GTech::IdName {
        enum class ProjectionType {ORTO, PERS};
        union {
            float mag;
            float fov;
        }x;
        float aspect_ratio{};
        float znear{0.1f};
        float zfar{100.0f};
        ProjectionType projectionType{ProjectionType::PERS};

    };

    struct Light : public GTech::IdName {
        enum class LightType {POINT};
        float constant_attenuation{1.0f};
        float linear_attenuaton{0.0f};
        float quadratic_attenuation{0.001111f};

        glm::vec3 color{1.0f, 0.0f, 0.0f};
        LightType lightType{GTech::Light::LightType::POINT};


    };

    using IdxSz = std::pair<unsigned int, unsigned int >; //Index and sizes;
    struct Mesh : public GTech::IdName {

        //PAIR INDEX , SIZE
        IdxSz vertices{std::make_pair(0,0)};
        IdxSz normals{std::make_pair(0,0)};
        IdxSz texcoords{std::make_pair(0,0)};

        enum class DataType {NONE, TEXCOORDS, NORMALS, VERTICES};
        std::stringstream   temporalStringStream{};
        std::string         temporalStrideXYZ{};
        Mesh::DataType      temporalDataType{Mesh::DataType::NONE};
        unsigned int        temporalNextIndexToWrite{0};
    };

    struct Material : public GTech::IdName{

    	void setIdName(const tinyxml2::XMLAttribute* pa, std::string stringToStrip){

    	    assert(pa);
    	    if (pa) id = pa->Value();
            auto stripIndex = id.find(stringToStrip);
            name = id.substr(0, stripIndex);

    	}

    	glm::vec4   emission;
        glm::vec4   ambient;
        glm::vec4   diffuse;
        glm::vec4   specular;
        float       shininess;

    };

    struct Scene : public GTech::IdName {

        std::string authoring_tool;
        std::string created;
        std::string modified;

        bool z_up{false};
        std::map<std::string, GTech::Camera> cameras{};
        std::map<std::string, GTech::Light> lights{};
        std::map<std::string, GTech::Material> materials{};
        std::map<std::string, GTech::Mesh> meshes{};
        std::vector<float> geometricalData{};


    };



}

GTech::Scene aScene;
GTech::Camera aCamera;
GTech::Light aLight;
GTech::Material aMaterial;
GTech::Mesh aMesh;

class ColladaVisitor : public XMLVisitor {



public:
    enum class VisitorState{
        none,
    	asset,
        library_cameras,
        library_lights,
        library_images,
        library_effects,
        library_materials,
        library_geometries,
        library_controllers,
        library_visual_scenes,
        scene
    };
private:
    std::map<std::string, ColladaVisitor::VisitorState > stateMap {
        std::make_pair("none",                  ColladaVisitor::VisitorState::none),
    	std::make_pair("asset",					ColladaVisitor::VisitorState::asset),
        std::make_pair("library_cameras",		ColladaVisitor::VisitorState::library_cameras),
        std::make_pair("library_lights",		ColladaVisitor::VisitorState::library_lights),
        std::make_pair("library_images",		ColladaVisitor::VisitorState::library_images),
        std::make_pair("library_effects",		ColladaVisitor::VisitorState::library_effects),
        std::make_pair("library_materials",		ColladaVisitor::VisitorState::library_materials),
        std::make_pair("library_geometries",	ColladaVisitor::VisitorState::library_geometries),
        std::make_pair("library_controllers",	ColladaVisitor::VisitorState::library_controllers),
        std::make_pair("library_visual_scenes",	ColladaVisitor::VisitorState::library_visual_scenes),
        std::make_pair("scene",					ColladaVisitor::VisitorState::scene)
    };
public:
    VisitorState visitorState{VisitorState::none};

    bool VisitEnter(const XMLElement& e, const XMLAttribute* pa)
    {
        auto eName = std::string{e.Name()};
        auto eNameSearchForVisitorState = stateMap.find(eName);
        auto eNameStateFound = eNameSearchForVisitorState != stateMap.end();

        if 	( eNameStateFound ){

            auto& visitorStateName = eName;
        	visitorState = stateMap[visitorStateName];

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

    bool VisitExit(const XMLElement& e){

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

};
int main (){

	XMLDocument doc;
	doc.LoadFile("../simple.dae");

    ColladaVisitor visitor;
    auto pVisitor = &visitor;
    doc.Accept(pVisitor);

	return 0;
}
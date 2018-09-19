#include "tinyxml2/tinyxml2.h"

#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace tinyxml2;
using namespace std;


namespace GTech {
    struct IdName {
        std::string id;
        std::string name;
        virtual void setIdName(const tinyxml2::XMLAttribute* pa){
            id = pa->Value();
            name = pa->Next()->Value();
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
        struct {
            float r{1.0f};
            float g{0.0f};
            float b{0.0f};
        }color;
        LightType lightType{GTech::Light::LightType::POINT};
    };

    struct ShadingModel : public GTech::IdName{

    	void setIdName(const tinyxml2::XMLAttribute* pa){
    		id = pa->Value();
    	}

        struct {
            float r,g,b,a;
        }emission;
        struct {
            float r,g,b,a;
        }ambient;
        struct {
            float r,g,b,a;
        }diffuse;
        struct {
            float r,g,b,a;
        }specular;
        float shininess;
    };
    struct Scene : public GTech::IdName {

        std::string authoring_tool;
        std::string created;
        std::string modified;


        bool z_up{false};
        std::map<std::string, GTech::Camera> cameras{};
        std::map<std::string, GTech::Light> lights{};
        std::map<std::string, GTech::ShadingModel> shadingmodels{};
        std::vector<float> vertices{};

    };



}

GTech::Scene aScene;
GTech::Camera aCamera;
GTech::Light aLight;

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
            if (visitorState == VisitorState::library_lights){

                colorText >> aLight.color.r;
                colorText >> aLight.color.g;
                colorText >> aLight.color.b;

            } else if (visitorState == VisitorState::library_effects){


            }
        }

        return true;
    }
    bool VisitExit(const XMLElement& e){

        auto eName = std::string{e.Name()};

        if (eName == "camera"){

            aScene.cameras[aCamera.id] = aCamera;
        }
        else if (eName == "light"){

            aScene.lights[aLight.id] = aLight;

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
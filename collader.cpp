#include "tinyxml2/tinyxml2.h"

#include <iostream>
#include <map>

using namespace tinyxml2;
using namespace std;


namespace GTech {
    struct IdName {
        std::string id;
        std::string name;
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

    struct Scene : public GTech::IdName {

        std::string authoring_tool;
        std::string created;
        std::string modified;


        bool z_up{false};
        std::map<std::string, GTech::Camera> cameras{};

    };

    struct Light : public GTech::IdName {

        float constant_attenuation{1f};
        float linear_attenuaton{0f};
        float quadratic_attenuation{0.001111f};
        struct {
            float r;
            float g;
            float b;
        };
    };
    struct PointLight : public GTech::Light {

        float x, float y, float z; 

    };

}

GTech::Scene aScene;
GTech::Camera aCamera;
GTech::Light aLight;

class ColladaVisitor : public XMLVisitor {



public:
    bool VisitEnter(const XMLElement& e, const XMLAttribute* pa)
    {
        auto eName = std::string{e.Name()};

        if (eName == "authoring_tool") {

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

            aCamera.id = pa->Value();
            aCamera.name = pa->Next()->Value();

        } else if (eName == "light") {

            aLight = GTech::Li
        }

        return true;
    }
    bool VisitExit(const XMLElement& e){

        auto eName = std::string{e.Name()};

        if (eName == "camera"){

            aScene.cameras[aCamera.name] = aCamera;
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
#include "tinyxml2/tinyxml2.h"
#include "glm/glm.hpp"

#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
namespace GTech {


    struct IdName {
        std::string id;
        std::string name;
        glm::vec3 color;
        virtual void SetIdName(const tinyxml2::XMLAttribute *pa){
            assert(pa != nullptr);
            if (pa) id = pa->Value();
            auto next = pa->Next();
            assert(next != nullptr);
            if (next) name = next->Value();
        }
    };
    struct Image : public IdName {

        std::string path{};

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

    struct InputDataConfig {

        enum class DataType {NONE, TEXCOORDS, NORMALS, VERTICES};
        GTech::InputDataConfig::DataType    dataType{InputDataConfig::DataType::NONE};
        std::string                         sourceId{};
        unsigned int                        offset{0};
    
    };

    struct TriangleArray {
        
        unsigned int                    count{0};
        std::string                     materialId{};
        std::vector<InputDataConfig>    indexArrayInputConfiguration{};
        std::vector<unsigned int>       indexes{};
    
    };

    struct Mesh : public GTech::IdName {

        enum class DataType {NONE, TEXCOORDS, NORMALS, VERTICES};
        std::map<std::string, unsigned int> offsetMap{};
        std::map<std::string, unsigned int> sizeMap{};
        std::vector<float>                  floatVector{};
        std::vector<GTech::TriangleArray>   triangleArray{};

    };

    struct Shader : public GTech::IdName{


    	enum class ShaderType {BLINN, CONSTANT, LAMBERT, PHONG};


    	glm::vec4   			emission;
        glm::vec4   			ambient;
        glm::vec4   			diffuse;
        glm::vec4   			specular;
        glm::vec4				reflective;
        float       			shininess;
        float					refractionIndex;
        Shader::ShaderType	    shaderType;
        std::string             imageId{};
    };

    struct Material : public GTech::IdName {

        GTech::Shader*          pShader{nullptr};

    };

    struct Scene : public GTech::IdName {

        std::string authoring_tool;
        std::string created;
        std::string modified;

        bool z_up{false};
        std::map<std::string, GTech::Camera> cameras{};
        std::map<std::string, GTech::Light> lights{};
        std::map<std::string, GTech::Shader> shaders{};
        std::map<std::string, GTech::Mesh> meshes{};
        std::map<std::string, GTech::Image> images{};
        std::map<std::string, GTech::Material> materials{};
        std::vector<float> geometricalData{};


    };


    class ColladaVisitor : public tinyxml2::XMLVisitor {



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
    	
        glm::vec4* tmpv4ptr{nullptr};
    	float*     tmpfloatptr{nullptr};

    	std::map<std::string, GTech::IdName*> nodePtrMap;

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

        bool VisitEnter_library_effects(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
        bool VisitEnter_library_images(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
        bool VisitEnter_library_materials(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
        bool VisitEnter_library_geometries(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);


	public:
	    VisitorState visitorState{VisitorState::none};
	    bool VisitEnter(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
		bool VisitExit(const tinyxml2::XMLElement& e);
	    	    

	};
}
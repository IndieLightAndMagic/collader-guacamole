#ifndef __COLLADER_H__
#define __COLLADER_H__


#include "tinyxml2/tinyxml2.h"
#include "glm/glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <string>
#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

#include "idname.h"
#include "camera.h"
#include "image.h"
namespace GTech {



    
    
    struct Light : public GTech::IdName {

        enum class LightType {POINT, SPOT, SUN};
        float constant_attenuation{0.0f};
        float linear_attenuaton{0.0f};
        float quadratic_attenuation{0.0f};

        glm::vec3 color{1.0f, 0.0f, 0.0f};
        LightType lightType{GTech::Light::LightType::POINT};
        
    };

    struct MeshSource {

        unsigned int    pointsCount{0};
        unsigned int    stride{0};
        std::string     axisOrder{};
        unsigned int    index;
        unsigned int    size;

    };

    struct MeshTrianglesInput {

        enum class DataType {NONE, TEXCOORD, NORMAL, VERTEX};
        GTech::MeshTrianglesInput::DataType	semanticType{MeshTrianglesInput::DataType::NONE};
        std::string                         source{};
        unsigned int                        offset{0};
        
        std::map<std::string, GTech::MeshTrianglesInput::DataType> semanticTypeMap{
            std::make_pair("VERTEX", GTech::MeshTrianglesInput::DataType::VERTEX),
            std::make_pair("NORMAL", GTech::MeshTrianglesInput::DataType::NORMAL),
            std::make_pair("TEXCOORD", GTech::MeshTrianglesInput::DataType::TEXCOORD)
        };             

        
    };

    struct MeshTriangles {
        
        unsigned int                    count{0};
        std::string                     material{};
        std::vector<MeshTrianglesInput> meshTrianglesInput{};
        std::vector<unsigned int>       indexArray{};

        
    };

    struct Mesh : public GTech::IdName {

        std::map<std::string, GTech::MeshSource>    meshSourceMap{};
        std::vector<GTech::MeshTriangles>           triangleArray{};
        std::vector<float>                          floatVector{};
        
    };

    struct Effect : public GTech::IdName{


    	enum class ShaderType {BLINN, CONSTANT, LAMBERT, PHONG};
        std::map<std::string, GTech::Effect::ShaderType> shadertypemap {
            std::make_pair("blinn", GTech::Effect::ShaderType::BLINN),
            std::make_pair("phong", GTech::Effect::ShaderType::PHONG),
            std::make_pair("lambert", GTech::Effect::ShaderType::LAMBERT),
            std::make_pair("constant", GTech::Effect::ShaderType::CONSTANT)
        };


    	glm::vec4   			emission;
        glm::vec4   			ambient;
        glm::vec4   			diffuse;
        glm::vec4   			specular;
        glm::vec4				reflective;
        float       			shininess;
        float					refractionIndex;
        Effect::ShaderType	    shaderType;
        std::string             imageId{};

    };

    struct Material : public GTech::IdName {

        std::string     effectUrl{};

    };

    struct Node : public GTech::IdName {

        enum class NodeType {CAMERA, MESH, LIGHT};
        std::map <std::string, GTech::Node::NodeType> nodeTypeMap{
            std::make_pair(std::string{"instance_camera"},  GTech::Node::NodeType::CAMERA),
            std::make_pair(std::string{"instance_light"},   GTech::Node::NodeType::LIGHT),
            std::make_pair(std::string{"instance_geometry"}, GTech::Node::NodeType::MESH)
        };
        glm::mat4                           transform;
        std::string                         url{};
        std::map<std::string, std::string>  instanced_materials{};
        Node::NodeType                      nodeType{};
        
    };

    struct Scene : public GTech::IdName {

        bool z_up{false};

        std::string authoring_tool{};
        std::string created{};
        std::string modified{};


        std::map<std::string, GTech::Node> nodes{};
        std::map<std::string, GTech::Mesh> meshes{};
        std::map<std::string, GTech::Camera> cameras{};
        std::map<std::string, GTech::Light> lights{};

        //--------- These are referenced by the above ----------//
        std::map<std::string, GTech::Effect> shaders{};
        std::map<std::string, GTech::Image> images{};
        std::map<std::string, GTech::Material> materials{};
        std::vector<float> geometricalData{};

        std::map<std::string, GTech::IdName*> nodePtrMap;



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
    	
        GTech::Node aNode;
        GTech::Mesh aMesh;
        GTech::Scene aScene;
        GTech::Light aLight;
        GTech::Image anImage;
        GTech::Camera aCamera;
        GTech::Effect aShader;
        GTech::Material aMaterial;
        GTech::MeshSource aMeshSource;
        GTech::MeshTriangles aMeshTriangles;

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
        bool VisitEnter_library_cameras(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
        bool VisitEnter_library_lights(const tinyxml2::XMLElement &e, const tinyxml2::XMLAttribute *pa);
        bool VisitEnter_library_visual_scenes(const tinyxml2::XMLElement &e, const tinyxml2::XMLAttribute *pa);

        bool VisitExit_library_geometries(const tinyxml2::XMLElement& e);
        bool VisitExit_library_images(const tinyxml2::XMLElement& e);
        bool VisitExit_library_cameras(const tinyxml2::XMLElement& e);
        bool VisitExit_library_materials(const tinyxml2::XMLElement& e);
        bool VisitExit_library_effects(const tinyxml2::XMLElement& e);
        bool VisitExit_library_lights(const tinyxml2::XMLElement &e);
        bool VisitExit_library_visual_scenes(const tinyxml2::XMLElement &e);

	public:
	    VisitorState visitorState{VisitorState::none};
	    bool VisitEnter(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
		bool VisitExit(const tinyxml2::XMLElement& e);
	    	    

    //Utils
        using AttrMap = std::map<std::string, std::string>;
        AttrMap GetAttrMap (const tinyxml2::XMLAttribute* pa){

            auto attrMap = AttrMap{}; 
            for (;pa; pa = pa->Next()){
                attrMap[std::string{pa->Name()}] = std::string{pa->Value()};
            }
            return attrMap;
        }
        AttrMap GetAttrMapParent(const tinyxml2::XMLElement& e){

            //Get Parent dict
            auto ppa = reinterpret_cast<const tinyxml2::XMLElement*>(e.Parent())->FirstAttribute();
            auto attrMapParent = GetAttrMap(ppa);

            return attrMapParent;    

        }

        std::string GetElementText(const tinyxml2::XMLElement& e);

        std::string GetParentName(const tinyxml2::XMLElement& e){

            //Get Parent dict
            return std::string{reinterpret_cast<const tinyxml2::XMLElement*>(e.Parent())->Name()};
            
        }
        

        const Scene& GetScene(){
            return aScene;
        }

        void PrintSceneInfo();
	};
}

#endif


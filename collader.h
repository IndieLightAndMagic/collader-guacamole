#ifndef __COLLADER_H__
#define __COLLADER_H__


#include "tinyxml2/tinyxml2.h"
#include "glm/glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"


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
        virtual void SetIdName(const tinyxml2::XMLAttribute *pa){
            assert(pa != nullptr);
            if (pa) id = pa->Value();
            auto next = pa->Next();
            assert(next != nullptr);
            if (next) name = next->Value();
        }
        virtual void Print(std::string tab = std::string{'\t'}){

            std::cout << "\n";
            std::cout << tab << "id:  " << id << "\n";
            std::cout << tab << "name:" << id << "\n";
                
        }
    };
    struct Image : public IdName {

        std::string path{};

    };
    struct Camera : public GTech::IdName {
        enum class ProjectionType {ORTO, PERS};
        union {
            float xmag;
            float yfov;
        }projection;
        float aspect_ratio{};
        float znear{0.1f};
        float zfar{100.0f};
        ProjectionType projectionType{ProjectionType::PERS};
        void Print(std::string tab = std::string{'\t'}){

            std::cout << "\n";
            std::cout << tab << "Camera:\n";
            IdName::Print(tab);
            auto projectionTypeString = projectionType == ProjectionType::PERS ? std::string{"perspective yfov: "} : std::string{"ortographic xmag: "};
            std::cout << tab << "Projection Type: " << projectionTypeString << projection.yfov << "\n";
            std::cout << tab << "zrange [ " << zfar << ", " << znear << " ]\n";
            
        }
    };

    struct Light : public GTech::IdName {

        enum class LightType {POINT, SPOT, SUN};
        float constant_attenuation{0.0f};
        float linear_attenuaton{0.0f};
        float quadratic_attenuation{0.0f};

        glm::vec3 color{1.0f, 0.0f, 0.0f};
        LightType lightType{GTech::Light::LightType::POINT};

        void Print(std::string tab = std::string{'\t'}){

            std::cout << "" << std::endl;
            std::cout << tab << "Light:" << std::endl;
            IdName::Print(tab);
            auto lightTypeString = (lightType == LightType::POINT) ? std::string{"Point"} : ( (lightType == LightType::SPOT) ? std::string{"Spot"} : std::string{"Sun"} );
            std::cout << tab << "Light Type: " << lightTypeString << "" << std::endl;
            std::cout << tab << "Attenuation: " << std::endl;
            std::cout << tab << " K: " << constant_attenuation << "" << std::endl;
            std::cout << tab << " L: " << linear_attenuaton << "" << std::endl;
            std::cout << tab << " Q: " << quadratic_attenuation << "" << std::endl;
            std::cout << tab << "Color: " << glm::to_string(color)<< "" << std::endl;
            
        }


    };

    struct MeshSource {

        unsigned int    pointsCount{0};
        unsigned int    stride{0};
        std::string     axisOrder{};
        unsigned int    index;
        unsigned int    size;

        void Print(std::string tab = std::string{'\t'}){

            std::cout << tab << "Stride: " << stride << std::endl;
            std::cout << tab << "AxisOrder: " << stride << std::endl;
            std::cout << tab << "Index: " << index << std::endl;
            std::cout << tab << "Size: " << size  << std::endl;

        }

    };

    struct MeshTrianglesInput {

        enum class DataType {NONE, TEXCOORD, NORMAL, VERTEX};
        GTech::MeshTrianglesInput::DataType	semantic{MeshTrianglesInput::DataType::NONE};
        std::string                         source{};
        unsigned int                        offset{0};

        void Print(std::string tab = std::string{'\t'}) {

            std::map<MeshTrianglesInput::DataType, std::string> semanticstringMap{
                std::make_pair(DataType::NONE, std::string{"NONE"}),
                std::make_pair(DataType::TEXCOORD, std::string{"TEXCOORD"}),
                std::make_pair(DataType::NORMAL, std::string{"NORMAL"}),
                std::make_pair(DataType::VERTEX, std::string{"VERTEX"})
            };
            
            std::cout << tab << "Semantic: " << semanticstringMap[semantic] << std::endl;
            std::cout << tab << "Source: " << source << std::endl;
            std::cout << tab << "Offset: " << offset << std::endl;

        }
    
    };

    struct MeshTriangles {
        
        unsigned int                    count{0};
        std::string                     material{};
        std::vector<MeshTrianglesInput> meshTrianglesInput;
        std::vector<unsigned int>       indexArray;

        void Print(std::string tab = std::string{'\t'} ){

            std::cout << tab << "Count: " << count << std::endl;
            std::cout << tab << "Material: " << material << std::endl;
            std::cout << tab << "Triangles Inputs: " << std::endl;
            
            for (auto& meshTriangleInput : meshTrianglesInput){
                meshTriangleInput.Print(tab+'\t');
            }

            std::cout << tab << "Indexes Array: ";
            
            for (auto& index: indexArray){

                std::cout << index << ", ";  

            }
            std::cout << std::endl;

        }

    };

    struct Mesh : public GTech::IdName {

        std::map<std::string, GTech::MeshSource>    meshSourceMap{};
        std::vector<GTech::MeshTriangles>           triangleArray{};
        std::vector<float>                          floatVector{};
        
        void Print(std::string tab = std::string{'\t'}){

            std::cout << std::endl;
            std::cout << tab << "Mesh: " << std::endl;
            IdName::Print(tab);

            for (auto& meshname_meshsource: meshSourceMap){

                auto meshName   = meshname_meshsource.first;
                auto meshSource = meshname_meshsource.second;

                std::cout << tab << "Mesh Name: " << meshName << std::endl;  
                meshSource.Print(tab+'\t');

            }
            
            std::cout << tab << "Triangle Arrays: " << std::endl;
            for (auto &anArray : triangleArray){
                anArray.Print(tab+'\t');
            }
            
            std::cout << tab << "Float Data: ";
            for (auto &aFloat: floatVector){
                std::cout << aFloat << ", ";
            }            
            
            std::cout << std::endl;

        }

    };

    struct Effect : public GTech::IdName{


    	enum class ShaderType {BLINN, CONSTANT, LAMBERT, PHONG};


    	glm::vec4   			emission;
        glm::vec4   			ambient;
        glm::vec4   			diffuse;
        glm::vec4   			specular;
        glm::vec4				reflective;
        float       			shininess;
        float					refractionIndex;
        Effect::ShaderType	    shaderType;
        std::string             imageId{};

        void Print(std::string tab = std::string{'\t'} ){

            std::cout << std::endl;
            std::cout << tab << "Effect:" << std::endl; 

        	std::map<ShaderType, std::string>shaderTypeMap {
        		std::make_pair(ShaderType::BLINN, "blinn"),
        		std::make_pair(ShaderType::CONSTANT, "constant"),
        		std::make_pair(ShaderType::LAMBERT, "lambert"),
        		std::make_pair(ShaderType::PHONG, "phong"),
        	};
            auto shaderTypeString = shaderTypeMap[shaderType];
            
            std::cout << tab << "Image Id: " << imageId;
            std::cout << tab << "ShaderType: " << shaderTypeString << std::endl;
            std::cout << tab << "Emission: " << glm::to_string(emission) << std::endl;      
            std::cout << tab << "Ambient: " << glm::to_string(ambient) << std::endl;      
            std::cout << tab << "Diffuse: " << glm::to_string(diffuse) << std::endl;      
            std::cout << tab << "Specular: " << glm::to_string(specular) << std::endl;
            std::cout << tab << "Shininess: " << shininess << std::endl;
            std::cout << tab << "Refraction Index: " << refractionIndex << std::endl;

        }

    };

    struct Material : public GTech::IdName {

        GTech::Effect*          pShader{nullptr};

        void Print(std::string tab = std::string{'\t'}){

            std::cout << std::endl;
            std::cout << "Material:" << std::endl;

            IdName::Print(tab);
            if (pShader){
            	pShader->Print(tab);
            }
        }

    };

    struct Node : public GTech::IdName {

        glm::mat4                           transform;
        std::string                         url{};
        std::map<std::string, std::string>  instanced_materials{};
        std::string                         instanceType{};
        
        void Print(std::string tab = std::string{'\t'}){

            std::cout << std::endl;
            std::cout << "Node" << std::endl;
            IdName::Print(tab);
            std::cout << "Instance Type: " << instanceType;
            
        }        

    };

    struct Scene : public GTech::IdName {

        std::string authoring_tool;
        std::string created;
        std::string modified;

        bool z_up{false};
        std::map<std::string, GTech::Node> nodes{};
        std::map<std::string, GTech::Camera> cameras{};
        std::map<std::string, GTech::Light> lights{};
        std::map<std::string, GTech::Effect> shaders{};
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


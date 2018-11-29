#ifndef __COLLADER_H__
#define __COLLADER_H__


#include "tinyxml2/tinyxml2.h"
#include "glm/glm.hpp"

#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <deque>
#include <tuple>
#include <map>

#include "scene.h"

namespace GTech {

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
            newparam,
            scene
        };
    private:
        

        std::shared_ptr<GTech::Scene> aScene{std::make_shared<GTech::Scene>()};

        std::map<std::string, ColladaVisitor::VisitorState > stateMap {
            
            std::make_pair("asset",                 ColladaVisitor::VisitorState::asset),
            std::make_pair("library_cameras",       ColladaVisitor::VisitorState::library_cameras),
            std::make_pair("library_lights",        ColladaVisitor::VisitorState::library_lights),
            std::make_pair("library_images",        ColladaVisitor::VisitorState::library_images),
            std::make_pair("library_effects",       ColladaVisitor::VisitorState::library_effects),
            std::make_pair("library_materials",     ColladaVisitor::VisitorState::library_materials),
            std::make_pair("library_geometries",    ColladaVisitor::VisitorState::library_geometries),
            std::make_pair("library_controllers",   ColladaVisitor::VisitorState::library_controllers),
            std::make_pair("library_visual_scenes", ColladaVisitor::VisitorState::library_visual_scenes),
            std::make_pair("none",                  ColladaVisitor::VisitorState::none),
            std::make_pair("newparam",              ColladaVisitor::VisitorState::newparam),
            std::make_pair("scene",                 ColladaVisitor::VisitorState::scene)
        
        };

        bool VisitEnter_library_effects(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
        bool VisitEnter_library_images(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
        bool VisitEnter_library_materials(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
        bool VisitEnter_library_geometries(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
        bool VisitEnter_library_cameras(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa);
        bool VisitEnter_library_lights(const tinyxml2::XMLElement &e, const tinyxml2::XMLAttribute *pa);
        bool VisitEnter_library_visual_scenes(const tinyxml2::XMLElement &e, const tinyxml2::XMLAttribute *pa);
        bool VisitEnter_newparam(const tinyxml2::XMLElement &e, const tinyxml2::XMLAttribute *pa);

        bool VisitExit_library_geometries(const tinyxml2::XMLElement& e);
        bool VisitExit_library_images(const tinyxml2::XMLElement& e);
        bool VisitExit_library_cameras(const tinyxml2::XMLElement& e);
        bool VisitExit_library_materials(const tinyxml2::XMLElement& e);
        bool VisitExit_library_effects(const tinyxml2::XMLElement& e);
        bool VisitExit_library_lights(const tinyxml2::XMLElement &e);
        bool VisitExit_library_visual_scenes(const tinyxml2::XMLElement &e);
        bool VisitExit_newparam(const tinyxml2::XMLElement &e);

        template <typename T>
        std::shared_ptr<T> CreateElement(const tinyxml2::XMLAttribute* pa){
            
            auto p = std::make_shared<T>();
            
            if ( p ) {

                p->SetIdName(pa);
                aScene->urlPtrMap[p->id]    = p;
                return p;
            
            } else return nullptr;  
            
        }
    public:
        

        std::deque<VisitorState> visitorStateDq{VisitorState::none};
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

        std::string GetParentName(const tinyxml2::XMLElement& e);        

        std::shared_ptr<const Scene> GetScene(){
            return aScene;
        }

        std::tuple<std::string, std::string, const char*> GetNameParentText(const tinyxml2::XMLElement& e);

        void PrintSceneInfo();
    };
}

#endif


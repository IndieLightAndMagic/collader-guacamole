#ifndef __COLLADER_H__
#define __COLLADER_H__

#include <QSharedPointer>
#include <QMap>
#include <QPair>
#include <QQueue>
#include <QStack>
#include <QFile>
#include "scene.h"

namespace QQE {

    class ColladaVisitor {



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
        ColladaVisitor(){
            visitorStateDqS.push(ColladaVisitor::VisitorState::none);
        }

    private:
        

        QSharedPointer<QQE::Scene> aScene{QSharedPointer<QQE::Scene>::create()};

        QMap<QString, ColladaVisitor::VisitorState > stateMap {
            
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

        bool VisitEnter_library_effects(const QDomElement& e, const QDomNamedNodeMap& pa);
        bool VisitEnter_library_images(const QDomElement& e, const QDomNamedNodeMap& pa);
        bool VisitEnter_library_materials(const QDomElement& e, const QDomNamedNodeMap& pa);
        bool VisitEnter_library_geometries(const QDomElement& e, const QDomNamedNodeMap& pa);
        bool VisitEnter_library_cameras(const QDomElement& e, const QDomNamedNodeMap& pa);
        bool VisitEnter_library_lights(const QDomElement& e, const QDomNamedNodeMap& pa);
        bool VisitEnter_library_visual_scenes(const QDomElement& e, const QDomNamedNodeMap& pa);
        bool VisitEnter_newparam(const QDomElement& e, const QDomNamedNodeMap& pa);

        bool VisitExit_library_geometries(const QDomElement& e);
        bool VisitExit_library_images(const QDomElement& e);
        bool VisitExit_library_cameras(const QDomElement& e);
        bool VisitExit_library_materials(const QDomElement& e);
        bool VisitExit_library_effects(const QDomElement& e);
        bool VisitExit_library_lights(const QDomElement& e);
        bool VisitExit_library_visual_scenes(const QDomElement& e);
        bool VisitExit_newparam(const QDomElement& e);

        template <typename T>
        QSharedPointer<T> CreateElement(const QDomNamedNodeMap& pa){
            
            auto p = QSharedPointer<T>::create();
            
            if ( p ) {

                p->SetIdName(pa);
                aScene->urlPtrMap[p->id]    = p.toWeakRef();
                return p;
            
            } else return nullptr;  
            
        }
    public:
        

        //std::deque<VisitorState> visitorStateDq{VisitorState::none};
        QQueue<VisitorState> visitorStateDqQ{};
        QStack<VisitorState> visitorStateDqS{};




        bool VisitEnter(const QDomElement& e, const QDomNamedNodeMap& pa);
        bool VisitExit(const QDomElement& e);

        void VisitNode(const QDomElement&, int);
        void LoadColladaDocument(QFile*);


        //Utils
        using AttrMap = QMap<QString, QString>;
        AttrMap GetAttrMap (const QDomNode& e){

            auto pa = e.attributes();
            auto attrMap = AttrMap{};
            auto attributesCount = pa.length();

            for (auto index = 0; index < attributesCount; ++index){

                auto attr = pa.item(index);
                auto attrName = attr.nodeName();
                auto attrValue = attr.nodeValue();
                attrMap[attrName] = attrValue;

            }

            return attrMap;

        }

        AttrMap GetAttrMapParent(const QDomNode& e){

            //Get Parent dict
            auto parentNode = e.parentNode();
            auto attrMapParent = GetAttrMap(parentNode);
            return attrMapParent;

        }

        QString GetElementText(const QDomElement& e);

        QString GetParentName(const QDomElement& e);

        QSharedPointer<const Scene> GetScene(){
            return aScene;
        }

        QPair<QString, QPair<QString, QString>> GetNameParentText(const QDomElement& e);

        void PrintSceneInfo();
    };
}

#endif


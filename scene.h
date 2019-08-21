#ifndef __SCENE_H__
#define __SCENE_H__


#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "idname.h"
#include "node.h"
#include "mesh.h"
#include "camera.h"
#include "light.h"
#include "effect.h"
#include "image.h"
#include "material.h"
#include "newparam.h"


namespace QQE {

    struct ColladaVisitor;
    
    struct Scene : public QQE::IdName {

        bool z_up{false};

        std::string authoring_tool{};
        std::string created{};
        std::string modified{};

        //---------- These are indexed with natural names ---------------//
        std::map<std::string, std::shared_ptr<QQE::Node>> nodes{};
        std::map<std::string, std::shared_ptr<QQE::Mesh>> meshes{};
        std::map<std::string, std::shared_ptr<QQE::Camera>> cameras{};
        std::map<std::string, std::shared_ptr<QQE::Light>> lights{};

        //--------- These are indexed with url and ids  ----------//
        std::map<std::string, std::shared_ptr<QQE::Effect>> shaders{};
        std::map<std::string, std::shared_ptr<QQE::Image>> images{};
        std::map<std::string, std::shared_ptr<QQE::Material>> materials{};
        std::map<std::string, std::shared_ptr<QQE::NewParam>> parameters{};
        std::map<char*, /*std::shared_ptr<QQE::IdName>*/void*> urlPtrMap;


    };




}

#endif

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

namespace GTech {


    struct Scene : public GTech::IdName {

        bool z_up{false};

        std::string authoring_tool{};
        std::string created{};
        std::string modified{};

        //---------- These are indexed with natural names ---------------//
        std::map<std::string, std::shared_ptr<GTech::Node>> nodes{};
        std::map<std::string, std::shared_ptr<GTech::Mesh>> meshes{};
        std::map<std::string, std::shared_ptr<GTech::Camera>> cameras{};
        std::map<std::string, std::shared_ptr<GTech::Light>> lights{};

        //--------- These are indexed with url and ids  ----------//
        std::map<std::string, std::shared_ptr<GTech::Effect>> shaders{};
        std::map<std::string, std::shared_ptr<GTech::Image>> images{};
        std::map<std::string, std::shared_ptr<GTech::Material>> materials{};
        std::map<std::string, std::shared_ptr<GTech::NewParam>> parameters{};
        std::map<std::string, std::shared_ptr<GTech::IdName>> urlPtrMap;

    };




}

#endif

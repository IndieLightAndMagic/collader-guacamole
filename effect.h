#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <map>

#include "idname.h"
#include "material.h"

namespace QQE {

    struct Effect : public QQE::IdName {

    	enum class ShaderType : unsigned int {
            BLINN = 0, 
            CONSTANT = 1, 
            LAMBERT = 2, 
            PHONG = 3 
        };
        
        std::map<std::string, QQE::Effect::ShaderType> shadertypemap {
            std::make_pair("blinn", QQE::Effect::ShaderType::BLINN),
            std::make_pair("phong", QQE::Effect::ShaderType::PHONG),
            std::make_pair("lambert", QQE::Effect::ShaderType::LAMBERT),
            std::make_pair("constant", QQE::Effect::ShaderType::CONSTANT)
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
        std::string             textureUrl{};
                    
    };



}

#endif
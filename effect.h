#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <map>

#include "idname.h"
#include "material.h"

namespace GTech {

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
        std::string             textureUrl{};
                    
    };



}

#endif
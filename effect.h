#ifndef __EFFECT_H__
#define __EFFECT_H__


#include "idname.h"
#include "material.h"
#include <QPair>
#include <QMatrix4x4>
namespace QQE {

    struct Effect : public QQE::IdName {

    	enum class ShaderType : unsigned int {
            BLINN = 0, 
            CONSTANT = 1, 
            LAMBERT = 2, 
            PHONG = 3 
        };
        
        QMap<QString, QQE::Effect::ShaderType> shadertypemap {
            std::make_pair("blinn", QQE::Effect::ShaderType::BLINN),
            std::make_pair("phong", QQE::Effect::ShaderType::PHONG),
            std::make_pair("lambert", QQE::Effect::ShaderType::LAMBERT),
            std::make_pair("constant", QQE::Effect::ShaderType::CONSTANT)

        };


    	QVector4D   			emission;
        QVector4D   			ambient;
        QVector4D   			diffuse;
        QVector4D   			specular;
        QVector4D				reflective;
        float       			shininess;
        float					refractionIndex;
        Effect::ShaderType	    shaderType;
        std::string             imageId{};
        std::string             textureUrl{};
                    
    };



}

#endif

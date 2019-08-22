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
        
        std::map<std::string, QQE::Effect::ShaderType> shadertypemap {
        QMap<QString, QQE::Effect::ShaderType> shadertypemap {};


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
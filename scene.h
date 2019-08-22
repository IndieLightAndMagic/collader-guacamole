#ifndef __SCENE_H__
#define __SCENE_H__




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

        QString authoring_tool{};
        QString created{};
        QString modified{};

        //---------- These are indexed with natural names ---------------//
        QMap<QString, QSharedPointer<QQE::Node>> nodes{};
        QMap<QString, QSharedPointer<QQE::Mesh>> meshes{};
        QMap<QString, QSharedPointer<QQE::Camera>> cameras{};
        QMap<QString, QSharedPointer<QQE::Light>> lights{};

        //--------- These are indexed with url and ids  ----------//
        QMap<QString, QSharedPointer<QQE::Effect>> shaders{};
        QMap<QString, QSharedPointer<QQE::Image>> images{};
        QMap<QString, QSharedPointer<QQE::Material>> materials{};
        QMap<QString, QSharedPointer<QQE::NewParam>> parameters{};
        QMap<QString, QWeakPointer<QQE::IdName>> urlPtrMap{};


    };




}

#endif

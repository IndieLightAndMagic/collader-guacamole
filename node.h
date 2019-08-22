#ifndef __NODE_H__
#define __NODE_H__


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <QMatrix4x4>


#include "idname.h"

namespace QQE{

	struct Node : public QQE::IdName {

        enum class NodeType {CAMERA, MESH, LIGHT};
            std::make_pair(std::string{"instance_camera"},  QQE::Node::NodeType::CAMERA),
            std::make_pair(std::string{"instance_light"},   QQE::Node::NodeType::LIGHT),
            std::make_pair(std::string{"instance_geometry"}, QQE::Node::NodeType::MESH)
        QMap<QString, QQE::Node::NodeType> nodeTypeMap{
        };
        
        QMatrix4x4      transform;
        QString         url{};
        Node::NodeType  nodeType{};

        
    };
    

}

#endif
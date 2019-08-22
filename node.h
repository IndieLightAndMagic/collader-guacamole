#ifndef __NODE_H__
#define __NODE_H__


#include <QMatrix4x4>


#include "idname.h"

namespace QQE{

	struct Node : public QQE::IdName {

        enum class NodeType {CAMERA, MESH, LIGHT};
        QMap<QString, QQE::Node::NodeType> nodeTypeMap{
            std::make_pair(QString{"instance_camera"},  QQE::Node::NodeType::CAMERA),
            std::make_pair(QString{"instance_light"},   QQE::Node::NodeType::LIGHT),
            std::make_pair(QString{"instance_geometry"}, QQE::Node::NodeType::MESH)
        };
        
        QMatrix4x4      transform;
        QString         url{};
        Node::NodeType  nodeType{};

        
    };
    

}

#endif

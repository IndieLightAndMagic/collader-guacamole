#ifndef __NODE_H__
#define __NODE_H__

#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>


#include "idname.h"

namespace QQE{

	struct Node : public QQE::IdName {

        enum class NodeType {CAMERA, MESH, LIGHT};
        std::map <std::string, QQE::Node::NodeType> nodeTypeMap{
            std::make_pair(std::string{"instance_camera"},  QQE::Node::NodeType::CAMERA),
            std::make_pair(std::string{"instance_light"},   QQE::Node::NodeType::LIGHT),
            std::make_pair(std::string{"instance_geometry"}, QQE::Node::NodeType::MESH)
        };
        
        glm::mat4                           transform;
        std::string                         url{};
        Node::NodeType                      nodeType{};

        
    };
    

}

#endif
#ifndef __NODE_H__
#define __NODE_H__

#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <ECS/Component/componentmanager.h>

#include "idname.h"

namespace GTech{

	struct Node : public GTech::IdName {

        enum class NodeType {CAMERA, MESH, LIGHT};
        std::map <std::string, GTech::Node::NodeType> nodeTypeMap{
            std::make_pair(std::string{"instance_camera"},  GTech::Node::NodeType::CAMERA),
            std::make_pair(std::string{"instance_light"},   GTech::Node::NodeType::LIGHT),
            std::make_pair(std::string{"instance_geometry"}, GTech::Node::NodeType::MESH)
        };
        glm::mat4                           transform;
        std::string                         url{};
        std::map<std::string, std::string>  instanced_materials{};
        Node::NodeType                      nodeType{};

        
        /**
         * @brief      Create a matrix component.
         *
         * @param[in]  rNode  reference to the node containing the matrix for it.
         *
         * @return     An unsigned integer of the id of the matrix component.
         */
        static unsigned int CreateMatrixComponent(const Node& rNode);
        
    };
    

}

#endif
#ifndef __MESH_H__
#define __MESH_H__


#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <ECS/Component/componentmanager.h>

#include "idname.h"

namespace GTech {

	struct MeshSource {

        unsigned int    pointsCount{0};
        unsigned int    stride{0};
        std::string     axisOrder{};
        unsigned int    index;
        unsigned int    size;

    };

    struct MeshTrianglesInput {

        enum class DataType {NONE, TEXCOORD, NORMAL, VERTEX};
        GTech::MeshTrianglesInput::DataType	semanticType{MeshTrianglesInput::DataType::NONE};
        std::string                         source{};
        unsigned int                        offset{0};
        
        std::map<std::string, GTech::MeshTrianglesInput::DataType> semanticTypeMap{
            std::make_pair("VERTEX", GTech::MeshTrianglesInput::DataType::VERTEX),
            std::make_pair("NORMAL", GTech::MeshTrianglesInput::DataType::NORMAL),
            std::make_pair("TEXCOORD", GTech::MeshTrianglesInput::DataType::TEXCOORD)
        };             

        
    };

    struct MeshTriangles {
        
        unsigned int                            count{0};
        std::string                             material{};
        std::vector<GTech::MeshTrianglesInput>  meshTrianglesInput{};
        std::vector<unsigned int>               indexArray{};

        
    };

    struct Mesh : public GTech::IdName {

        std::map<std::string, std::shared_ptr<GTech::MeshSource>>   meshSourceMap{};
        std::vector<std::shared_ptr<GTech::MeshTriangles>>          triangleArray{};
        std::vector<float>                                          floatVector{};
        
        static unsigned int CreateVaoArrayComponent(const Mesh& rMesh, const GTech::IdMap& rMap);
    };

}

#endif
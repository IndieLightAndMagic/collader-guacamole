#ifndef __MESH_H__
#define __MESH_H__


#include <iostream>
#include <string>
#include <map>
#include <vector>


#include "idname.h"

namespace QQE {

	struct MeshSource {

        unsigned int    pointsCount{0};
        unsigned int    stride{0};
        QString         axisOrder{};
        unsigned int    index;
        unsigned int    size;

    };

    struct MeshTrianglesInput {

        enum class DataType : unsigned int {
            NONE = 0xFFFFFFFF,
            COLOR = 0x03, 
            TEXCOORD = 0x02, 
            NORMAL = 0x01, 
            VERTEX = 0x00
        };
        QQE::MeshTrianglesInput::DataType	semanticType{MeshTrianglesInput::DataType::NONE};
        std::string                         source{};
        unsigned int                        offset{0};
        
        QMap<QString, QQE::MeshTrianglesInput::DataType> semanticTypeMap {
            std::make_pair("VERTEX", QQE::MeshTrianglesInput::DataType::VERTEX),
            std::make_pair("NORMAL", QQE::MeshTrianglesInput::DataType::NORMAL),
            std::make_pair("TEXCOORD", QQE::MeshTrianglesInput::DataType::TEXCOORD)

        };             

        
    };

    struct MeshTriangles {
        
        unsigned int                            count{0};
        std::string                             material{};
        std::vector<QQE::MeshTrianglesInput>  meshTrianglesInput{};
        std::vector<unsigned int>               indexArray{};

        
    };

    struct Mesh : public QQE::IdName {

        QMap<QString, QSharedPointer<QQE::MeshSource>>   meshSourceMap{};
        QVector<QSharedPointer<QQE::MeshTriangles>>      triangleArray{};
        QVector<float>                                   floatVector{};

    };

}

#endif

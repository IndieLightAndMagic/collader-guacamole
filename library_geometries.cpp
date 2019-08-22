//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"
#include <sstream>

QSharedPointer<QQE::Mesh> pMeshTmp                               = nullptr;
QSharedPointer<QQE::MeshSource> pMeshSourceTmp                   = nullptr;
QSharedPointer<QQE::MeshTriangles> pMeshTrianglesTmp             = nullptr;

bool QQE::ColladaVisitor::VisitExit_library_geometries(const QDomElement& e){

    auto eName = e.nodeName();
    
    if (eName == "triangles") {

        pMeshTmp->triangleArray.push_back(pMeshTrianglesTmp);
    
    }

    return true;
}

bool QQE::ColladaVisitor::VisitEnter_library_geometries(const QDomElement& e, const QDomNamedNodeMap& pa){

    auto eName = e.nodeName();
    auto parentName = GetParentName(e);
    
    //Get Attr dict
    auto attrMap = GetAttrMap(e);
    auto attrMapParent = GetAttrMapParent(e);

    if (eName == "geometry") {

        pMeshTmp                        = CreateElement<QQE::Mesh>(pa);
        aScene->meshes[pMeshTmp->name]   = pMeshTmp;

    } else if (eName == "source") {

        pMeshSourceTmp                          = QSharedPointer<QQE::MeshSource>::create();
        pMeshTmp->meshSourceMap[attrMap["id"]]  = pMeshSourceTmp;

    } else if (eName == "accessor") {

        std::stringstream{attrMap["count"].toStdString()}    >> pMeshSourceTmp->pointsCount;
        std::stringstream{attrMap["stride"].toStdString()}   >> pMeshSourceTmp->stride;

    } else if (eName == "param") {

        if (parentName == "accessor") {

            pMeshSourceTmp->axisOrder += attrMap["name"];

        }

    } else if (eName == "float_array") {
        
        //Get Mesh Index in the float array data
        pMeshSourceTmp->index                               =  pMeshTmp->floatVector.size();
        std::stringstream{attrMap["count"].toStdString()}    >> pMeshSourceTmp->size;
        
        //Resize Vector
        pMeshTmp->floatVector.resize(pMeshSourceTmp->index + pMeshSourceTmp->size);
        auto newSize = pMeshTmp->floatVector.size();

        //Parse the floats
        auto theFloats = std::stringstream{GetElementText(e).toStdString()};
        for (auto index = pMeshSourceTmp->index; index < newSize; index++){

            theFloats >> pMeshTmp->floatVector[index];

        }

    } else if (eName == "p") {

        auto size = pMeshTrianglesTmp->count * 3;
        auto indexArrayStream = std::stringstream{GetElementText(e).toStdString()};
        for (unsigned int pos = 0; pos < size; ++pos){
            
            unsigned int index;
            indexArrayStream >> index;
            pMeshTrianglesTmp->indexArray.push_back(index);

        }

    } else if (eName == "input") {

        if (parentName == "vertices"){

            auto idKey                                      = attrMap["source"].toStdString().data() + 1;
            pMeshTmp->meshSourceMap[attrMapParent["id"]]    = pMeshTmp->meshSourceMap[idKey];

        } else if (parentName == "triangles") {

            auto aMeshTriangleInput                 = QQE::MeshTrianglesInput{};
            aMeshTriangleInput.source               = attrMap["source"].toStdString().data() + 1;
            aMeshTriangleInput.semanticType         = aMeshTriangleInput.semanticTypeMap[attrMap["semantic"]];
            std::stringstream{attrMap["offset"].toStdString()} >> aMeshTriangleInput.offset;
            pMeshTrianglesTmp->meshTrianglesInput.push_back(aMeshTriangleInput);

        }

    } else if (eName == "triangles") {

        pMeshTrianglesTmp                       = QSharedPointer<QQE::MeshTriangles>::create();
        std::stringstream{attrMap["count"].toStdString()}     >> pMeshTrianglesTmp->count;
        std::stringstream{attrMap["material"].toStdString()}  >> pMeshTrianglesTmp->material;

    } 

    return true;
}
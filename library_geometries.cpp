//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"

using namespace tinyxml2;
using namespace std;

std::shared_ptr<GTech::Mesh> pMeshTmp                               = nullptr;
std::shared_ptr<GTech::MeshSource> pMeshSourceTmp                   = nullptr;
std::shared_ptr<GTech::MeshTriangles> pMeshTrianglesTmp             = nullptr;

bool GTech::ColladaVisitor::VisitExit_library_geometries(const XMLElement& e){

    auto eName = std::string{e.Name()};
    
    if (eName == "triangles") {

        pMeshTmp->triangleArray.push_back(pMeshTrianglesTmp);
    
    }

    return true;
}

bool GTech::ColladaVisitor::VisitEnter_library_geometries(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa){

    auto eName = std::string{e.Name()};
    auto parentName = GetParentName(e);
    
    //Get Attr dict
    auto attrMap = GetAttrMap(pa);
    auto attrMapParent = GetAttrMapParent(e);

    if (eName == "geometry") {

        pMeshTmp                        = CreateElement<GTech::Mesh>(pa);
        aScene.meshes[pMeshTmp->name]   = pMeshTmp;

    } else if (eName == "source") {

        pMeshSourceTmp = std::make_shared<GTech::MeshSource>();

    } else if (eName == "accesor") {

        std::stringstream{std::string{attrMap["count"]}}    >> pMeshSourceTmp->pointsCount;
        std::stringstream{std::string{attrMap["stride"]}}   >> pMeshSourceTmp->stride;

    } else if (eName == "param") {

        if (parentName == "accessor") {

            pMeshSourceTmp->axisOrder += std::string{attrMap["name"]};

        }

    } else if (eName == "float_array") {
        
        //Get Mesh Index in the float array data
        pMeshSourceTmp->index                               =  pMeshTmp->floatVector.size();
        std::stringstream{std::string{attrMap["count"]}}    >> pMeshSourceTmp->size;
        
        //Resize Vector
        pMeshTmp->floatVector.resize(pMeshSourceTmp->index + pMeshSourceTmp->size);
        auto newSize = pMeshTmp->floatVector.size();

        //Parse the floats
        auto theFloats = std::stringstream{GetElementText(e)};
        for (auto index = pMeshSourceTmp->index; index < newSize; index++){

            theFloats >> pMeshTmp->floatVector[index];

        }

    } else if (eName == "p") {

        auto size = pMeshTrianglesTmp->count * 3;
        auto indexArrayStream = std::stringstream{GetElementText(e)};
        for (unsigned int pos = 0; pos < size; ++pos){
            
            unsigned int index;
            indexArrayStream >> index;
            pMeshTrianglesTmp->indexArray.push_back(index);

        }

    } else if (eName == "input") {

        auto aMeshTriangleInput             = GTech::MeshTrianglesInput{};
        aMeshTriangleInput.source          = std::string{attrMap["source"].c_str() + 1};
        aMeshTriangleInput.semanticType    = aMeshTriangleInput.semanticTypeMap[attrMap["semantic"]];
        std::stringstream{attrMap["offset"]}    >> aMeshTriangleInput.source;
        pMeshTrianglesTmp->meshTrianglesInput.push_back(aMeshTriangleInput); 

    } else if (eName == "triangles") {

        pMeshTrianglesTmp                       = std::make_shared<GTech::MeshTriangles>();
        std::stringstream{attrMap["count"]}     >> pMeshTrianglesTmp->count;
        std::stringstream{attrMap["material"]}  >> pMeshTrianglesTmp->material;

    } 

    return true;
}
//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"

using namespace tinyxml2;
using namespace std;

bool GTech::ColladaVisitor::VisitExit_library_geometries(const XMLElement& e){

    auto eName = std::string{e.Name()};
    
    if (eName == "geometry") {
        
        aScene.meshes[aMesh.name]   = aMesh;
        aScene.nodePtrMap[aMesh.id] = &aScene.meshes[aMesh.name];
    
    } else if (eName == "triangles") {

        aMesh.triangleArray.push_back(aMeshTriangles);
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

        aMesh = GTech::Mesh{};
        aMesh.SetIdName(pa);

    } else if (eName == "source") {

        aMeshSource = GTech::MeshSource{};

    } else if (eName == "accesor") {

        std::stringstream{std::string{attrMap["count"]}}    >> aMeshSource.pointsCount;
        std::stringstream{std::string{attrMap["stride"]}}   >> aMeshSource.stride;

    } else if (eName == "param") {

        if (parentName == "accessor") {

            aMeshSource.axisOrder += std::string{attrMap["name"]};

        }

    } else if (eName == "float_array") {
        
        //Get Mesh Index in the float array data
        aMeshSource.index                                   =  aMesh.floatVector.size();
        std::stringstream{std::string{attrMap["count"]}}    >> aMeshSource.size;
        
        //Resize Vector
        aMesh.floatVector.resize(aMeshSource.index + aMeshSource.size);
        auto newSize = aMesh.floatVector.size();

        //Parse the floats
        auto theFloats = std::stringstream{GetElementText(e)};
        for (auto index = aMeshSource.index; index < newSize; index++){

            theFloats >> aMesh.floatVector[index];

        }

    } else if (eName == "p") {

        auto size = aMeshTriangles.count * 3;
        auto indexArrayStream = std::stringstream{GetElementText(e)};
        for (unsigned int pos = 0; pos < size; ++pos){
            
            unsigned int index;
            indexArrayStream >> index;
            aMeshTriangles.indexArray.push_back(index);

        }

    } else if (eName == "input") {

        auto aMeshTriangleInput                 = GTech::MeshTrianglesInput{};
        aMeshTriangleInput.source               = std::string{attrMap["source"].c_str() + 1};
        aMeshTriangleInput.semanticType             = aMeshTriangleInput.semanticTypeMap[attrMap["semantic"]];
        std::stringstream{attrMap["offset"]}    >> aMeshTriangleInput.source;
        aMeshTriangles.meshTrianglesInput.push_back(aMeshTriangleInput); 

    } else if (eName == "triangles") {

        aMeshTriangles                          = GTech::MeshTriangles{};
        std::stringstream{attrMap["count"]}     >> aMeshTriangles.count;
        std::stringstream{attrMap["material"]}  >> aMeshTriangles.material;

    } 

    return true;
}
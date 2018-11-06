#include "collader.h"
#include <FS/path.h>
#include <FS/resolver.h>


#include <tuple>
using namespace tinyxml2;
using namespace GTech;


std::tuple<std::string, std::string> resourceNameResolution(std::string spath){

    //Create Path
    auto path = GTech::filesystem::path{spath};

    //Create a string to store the resource name
    std::string resourceName{};

    //While the path doesn't exist and it is not empty:
    while (!path.exists() && !path.empty()){
        //Add path endpoint to the beginning of resourceName 
        resourceName = resourceName.empty() ? path.filename() : path.filename() + std::string{"/"} + resourceName;

        //Strip the endpoint out of path
        path = path.parent_path();
    }

    //If the path is empty or it doesn't exist return an empty string for the path and a resource name.
    if (path.empty() || !path.exists()){
        return std::make_tuple(std::string{}, resourceName);
    }

    //The path exists: return it and the resource name
    return std::make_tuple(path.str(), resourceName);

}

int main (){


    auto path = std::string{"Cube"};
    auto [resourceFile, resourceName] = resourceNameResolution(path);
    std::cout << resourceFile << ", " << resourceName << std::endl; 
    XMLDocument doc;
    doc.LoadFile("../../resources/simple.dae");

    ColladaVisitor visitor;
    auto pVisitor = &visitor;
    doc.Accept(pVisitor);
    auto aScene = visitor.GetScene();

    return 0;

}

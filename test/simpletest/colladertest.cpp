#include "collader.h"
#include <FS/path.h>
#include <FS/resolver.h>


#include <tuple>
using namespace tinyxml2;
using namespace GTech;


std::tuple<std::string, std::string> resourceNameResolution(std::string spath){

    auto path = GTech::filesystem::path{spath};
    std::string resourceName{};
    while (!path.exists() && !path.empty()){
        std::cout << path << " does not exists! stripping: " << path.filename() << std::endl;
        resourceName = resourceName.empty() ? path.filename() : path.filename() + std::string{"/"} + resourceName;
        path = path.parent_path();
    }
    std::cout << "***\n"<< path << "\n***\n" << std::endl;
    if (path.empty() || !path.exists()){
        std::cout << "Path never existed!!!!" << std::endl;
        return std::make_tuple(std::string{}, std::string{});
    }
    std::cout << "Abs Path is " << path.make_absolute() << std::endl;
    std::cout << "Rel Path is " << path << std::endl;
    
    return std::make_tuple(path.str(), resourceName);

}

int main (){


    auto path = std::string{"../../resources/simple.dae/Cube"};
    auto [resourceFile, resourceName] = resourceNameResolution(path);
    
    XMLDocument doc;
    doc.LoadFile("../../resources/simple.dae");

    ColladaVisitor visitor;
    auto pVisitor = &visitor;
    doc.Accept(pVisitor);
    auto aScene = visitor.GetScene();

    return 0;

}

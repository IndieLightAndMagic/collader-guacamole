#include "sceneresourcer.h"

#include <ECS/Entity/entitymanager.h>
#include <FS/path.h>
#include <FS/resolver.h>


using namespace tinyxml2;
using namespace GTech;

GTech::PairDocVisitorPtr GTech::ResourceManager::GetPairDocVisitorPtr(const std::string &resourceFilenamePathStr){

    if (GTech::ResourceManager::ResourceFileIsRegistered(resourceFilenamePathStr)){
        return map_SResourceName_PairDocVisitor[resourceFilenamePathStr];
    }

    return nullptr;
}

std::tuple<std::string, std::string> GTech::ResourceManager::ResourceNameResolution(const std::string& spath){

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

bool GTech::ResourceManager::RegisterResource(const std::string& resourceFilenamePathStr){
    
    if (GTech::ResourceManager::ResourceFileIsRegistered(resourceFilenamePathStr)) return true;

    //Resource is not registered yet. Register it. 
    auto pair_xmldoc_visitor_ptr                              = GTech::make_PairDocVisitorPtr();
    auto& xmldoc                                              = pair_xmldoc_visitor_ptr->first;
    auto loadfileresult                                       = xmldoc.LoadFile(resourceFilenamePathStr.c_str());
    auto& visitor                                             = pair_xmldoc_visitor_ptr->second;
    auto visitor_ptr                                          = &visitor;

    if (loadfileresult != tinyxml2::XML_SUCCESS) return false;
    
    map_SResourceName_PairDocVisitor[resourceFilenamePathStr] = pair_xmldoc_visitor_ptr; 
    return xmldoc.Accept(visitor_ptr);

}

bool GTech::ResourceManager::ResourceFileIsRegistered(const std::string& resourceFilenamePathStr){

    auto trytofindthisresource = map_SResourceName_PairDocVisitor.find(resourceFilenamePathStr);
    auto resourcewasnotfound = map_SResourceName_PairDocVisitor.end();
    auto resourceisalreadyregistered = trytofindthisresource != resourcewasnotfound;
    if (resourceisalreadyregistered) return true;

    return false;
}



unsigned int GTech::ResourceManager::Load(const std::string& resourceFileName){
    
    auto [resourceFile, resourceName] = GTech::ResourceManager::ResourceNameResolution(resourceFileName);
    auto resourcePath                 = GTech::filesystem::path{resourceFile}.make_absolute();
    auto resourcePathStr              = resourcePath.str();                


    if (!GTech::ResourceManager::ResourceFileIsRegistered(resourcePathStr))
        if (GTech::ResourceManager::RegisterResource(resourcePathStr) == false) return 0;
    
    auto pPairDocVisitor = GTech::ResourceManager::GetPairDocVisitorPtr(resourcePathStr);
    auto visitor         = pPairDocVisitor->second;
    auto scene           = visitor.GetScene();
    auto nodefound       = scene.nodes.find(resourceName) != scene.nodes.end();

    if (!nodefound) return 0;

    // Ok node was found... start creating components.
    auto pnode           = scene.nodes[resourceName];

    // Create Mtx Component.
    auto matrixComponent = GTech::Node::CreateMatrixComponent(*pnode);

    if (pnode->nodeType == GTech::Node::NodeType::MESH){

        auto ptr = scene.urlPtrMap[pnode->url];
        auto meshptr = std::dynamic_pointer_cast<GTech::Mesh>(ptr);
        auto  

    } else if (pnode->nodeType == GTech::Node::NodeType::CAMERA){



    } else if (pnode->nodeType == GTech::Node::NodeType::LIGHT) {



    }

    auto entitymanager   = ECS::EntityManager::GetInstance();
    auto eId             = entitymanager.CreateEntity();

    return 0;
}

void GTech::ResourceManager::UnLoad(const std::string &resourceName){
    
}

void GTech::ResourceManager::ClearCache(){

    map_SResourceName_PairDocVisitor.clear();

}


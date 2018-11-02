#include "sceneresourcer.h"

#include <ECS/Entity/entitymanager.h>


using namespace tinyxml2;
using namespace GTech;

unsigned int GTech::ResourceManager::Load(const std::string &resourceName){
    
    auto entitymanager = ECS::EntityManager::GetInstance();
    auto eId = entitymanager.CreateEntity();

    
    

    return 0;
}

void GTech::ResourceManager::UnLoad(const std::string &resourceName){
    
}

GTech::PXMLDoc GTech::ResourceManager::GetPXMLDoc(const std::string &resourceName){


    auto found = (map_SResourceName_PXMLDoc.find(resourceName) !=  map_SResourceName_PXMLDoc.end());
    if (found){
        return map_SResourceName_PXMLDoc[resourceName];
    }

    return nullptr;
}
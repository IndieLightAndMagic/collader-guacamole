#include "mesh.h"

using namespace GTech;

unsigned int GTech::Mesh::CreateVaoArrayComponent(const Mesh& rMesh, const IdMap& rMap){
	
	auto componentManager = ECS::ComponentManager::GetInstance();
	auto vaoArrayComponentId  = componentManager.CreateComponent<ECS::VaoArrayComponent_>();
	auto vaoArrayComponentPtr = componentManager.GetComponentRaw<ECS::VaoArrayComponent_>(vaoArrayComponentId);
	
	

	return 0;
}


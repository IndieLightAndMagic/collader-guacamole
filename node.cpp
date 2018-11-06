#include "node.h"

using namespace GTech;


unsigned int GTech::Node::CreateMatrixComponent(const Node& rNode){

    auto componentManager      = ECS::ComponentManager::GetInstance();
    auto matrixComponentId     = componentManager.CreateComponent<ECS::MatrixComponent_>();
    auto matrixComponentPtr    = componentManager.GetComponentRaw<ECS::MatrixComponent_>(matrixComponentId);
    matrixComponentPtr->matrix = rNode.transform;

    return matrixComponentId;
}



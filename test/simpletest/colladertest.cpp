#include "collader.h"


using namespace tinyxml2;
using namespace GTech;
int main (){

    XMLDocument doc;
    doc.LoadFile("../../resources/simple.dae");

    ColladaVisitor visitor;
    auto pVisitor = &visitor;
    doc.Accept(pVisitor);
    auto aScene = visitor.GetScene();

    return 0;

}

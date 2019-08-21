#include "collader.h"


#include <tuple>
using namespace tinyxml2;



int main (){


    XMLDocument doc;
    doc.LoadFile("/tmp/wolf/models/default.dae");

    QQE::ColladaVisitor visitor;
    auto pVisitor = &visitor;
    doc.Accept(pVisitor);
    auto aScene = visitor.GetScene();
    for ( auto&name_ptr : aScene->urlPtrMap){
        auto name = name_ptr.first;
        std::cout << name << std::endl;
    }
    return 0;

}

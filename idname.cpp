#include "idname.h"

using namespace QQE;
void IdName::SetIdName(const QDomNamedNodeMap& e){

    auto attrCount = e.length();

    for (auto index = 0; index < attrCount; ++index){

        auto attr = e.item(index);
        if (attr.nodeName() == "id"){
            id = attr.nodeValue();
        } else if (attr.nodeName() == "name") {
            name = attr.nodeValue();
        }

    }

}
        

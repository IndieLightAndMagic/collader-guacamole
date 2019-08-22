//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


QSharedPointer<QQE::Image> pImageTmp = nullptr;


bool QQE::ColladaVisitor::VisitExit_library_images(const QDomElement& e){

	return true;

}
bool QQE::ColladaVisitor::VisitEnter_library_images(const QDomElement& e, const QDomNamedNodeMap& pa){
    
    auto eName = e.nodeName();

    if( eName == "image"){


        pImageTmp                        = CreateElement<QQE::Image>(pa);
        aScene->images[pImageTmp->name]  = pImageTmp;

    } else if (eName == "init_from") {

        pImageTmp->path = GetElementText(e);

    }

    return true;
}

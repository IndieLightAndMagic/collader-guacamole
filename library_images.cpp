//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;
std::shared_ptr<GTech::Image> pImageTmp = nullptr;


bool GTech::ColladaVisitor::VisitExit_library_images(const tinyxml2::XMLElement &e){

	return true;

}
bool GTech::ColladaVisitor::VisitEnter_library_images(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa){
    
    auto eName = std::string{e.Name()};

    if( eName == "image"){


        pImageTmp                        = CreateElement<GTech::Image>(pa);
        aScene.images[pImageTmp->name]   = pImageTmp;

    } else if (eName == "init_from") {

        pImageTmp->path = GetElementText(e);

    }

    return true;
}

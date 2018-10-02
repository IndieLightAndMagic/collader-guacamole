//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

bool GTech::ColladaVisitor::VisitExit_library_images(const tinyxml2::XMLElement &e){

	auto eName = std::string{e.Name()};

	if (eName == "image"){

		aScene.images[anImage.name]	  = anImage;
		aScene.nodePtrMap[anImage.id] = &aScene.images[anImage.name];

	}
	return true;
}
bool GTech::ColladaVisitor::VisitEnter_library_images(const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* pa){
    
    auto eName = std::string{e.Name()};

    if( eName == "image"){
    
        anImage = GTech::Image{};
        anImage.SetIdName(pa);

    } else if (eName == "init_from") {

        anImage.path = GetElementText(e);

    }

    return true;
}

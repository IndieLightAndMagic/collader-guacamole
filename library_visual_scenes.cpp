//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

bool GTech::ColladaVisitor::VisitExit_library_visual_scenes(const tinyxml2::XMLElement &e){


	auto eName = std::string{e.Name()};
	if (eName == "visual_scene"){

		return true;

	} else if (eName == "node"){

		aScene.nodes[aNode.name] 	= aNode;
		aScene.nodePtrMap[aNode.id]	= &aScene.nodes[aNode.name];

	}
	return true;
}
bool GTech::ColladaVisitor::VisitEnter_library_visual_scenes(const tinyxml2::XMLElement &e, const tinyxml2::XMLAttribute *pa){

	auto eName = std::string{e.Name()};
	auto attrMap = GetAttrMap(pa);
	auto textString = std::stringstream{GetElementText(e)};

	if (eName == "visual_scene"){

		aScene.SetIdName(pa);

	} else if (eName == "node"){

		aNode = GTech::Node{};
		aNode.SetIdName(pa);

	} else if (eName == "matrix") {

		std::vector<glm::vec4> rows{};


		for (int index = 0; index < 4; ++index){
			
			float x,y,z,w;
			textString >> x; textString >> y; textString >> z; textString >> w;
			rows.push_back(glm::vec4{x,y,z,w});

		}
		
		aNode.transform = glm::mat4{rows[0], rows[1], rows[2], rows[3]};

	} else if (aNode.nodeTypeMap.find(eName) != aNode.nodeTypeMap.end()){

		auto pUrl 		= attrMap["url"].c_str() + 1;
		aNode.url 		= std::string{pUrl};
		aNode.nodeType 	= aNode.nodeTypeMap[eName];

	} else if (eName == "instance_material") {

		auto insmat_key	= attrMap["symbol"];
		auto insmat_val	= std::string{attrMap["target"].c_str() + 1};

		aNode.instanced_materials[insmat_key] = insmat_val;

	} 

	return true;
}
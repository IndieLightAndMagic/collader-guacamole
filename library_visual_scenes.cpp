//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

std::shared_ptr<QQE::Node> pNodeTmp;

bool QQE::ColladaVisitor::VisitExit_library_visual_scenes(const tinyxml2::XMLElement &e){

    return true;
}
bool QQE::ColladaVisitor::VisitEnter_library_visual_scenes(const tinyxml2::XMLElement &e, const tinyxml2::XMLAttribute *pa){

    auto eName = std::string{e.Name()};
    auto attrMap = GetAttrMap(pa);
    auto textString = std::stringstream{GetElementText(e)};

    if (eName == "visual_scene"){

        aScene->SetIdName(pa);

    } else if (eName == "node"){

        pNodeTmp                       = CreateElement<QQE::Node>(pa);
        aScene->nodes[pNodeTmp->name]   = pNodeTmp;

    } else if (eName == "matrix") {

        std::vector<glm::vec4> rows{};


        for (int index = 0; index < 4; ++index){
            
            float x,y,z,w;
            textString >> x; textString >> y; textString >> z; textString >> w;
            rows.push_back(glm::vec4{x,y,z,w});

        }
        
        pNodeTmp->transform = glm::mat4{rows[0], rows[1], rows[2], rows[3]};

    } else if (pNodeTmp->nodeTypeMap.find(eName) != pNodeTmp->nodeTypeMap.end()){

        auto pUrl           = attrMap["url"].c_str() + 1;
        pNodeTmp->url       = std::string{pUrl};
        pNodeTmp->nodeType  = pNodeTmp->nodeTypeMap[eName];

    } else if (eName == "instance_material") {

        auto symbol                 = attrMap["symbol"];
        auto target                 = std::string{attrMap["target"].c_str() + 1};
        
        for ( auto& url_idname: aScene->urlPtrMap){

            //Lookout for target
            if (url_idname.first != target) continue;

            //Target found, create a new entry pointer to the same idname;
            aScene->urlPtrMap[symbol.data()]    = url_idname.second;

        }

    }

    return true;
}
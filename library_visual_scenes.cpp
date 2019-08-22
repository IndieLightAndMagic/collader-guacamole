//http://www.wazim.com/Collada_Tutorial_1.htm
#include <QSharedPointer>
#include <QMatrix4x4>
#include <sstream>
#include "collader.h"



QSharedPointer<QQE::Node> pNodeTmp;

bool QQE::ColladaVisitor::VisitExit_library_visual_scenes(const QDomElement& e){

    return true;
}
bool QQE::ColladaVisitor::VisitEnter_library_visual_scenes(const QDomElement& e, const QDomNamedNodeMap& pa){

    auto eName = e.nodeName();
    auto attrMap = GetAttrMap(e);
    auto textString = std::stringstream{GetElementText(e).toStdString()};

    if (eName == "visual_scene"){

        aScene->SetIdName(pa);

    } else if (eName == "node"){

        pNodeTmp                       = CreateElement<QQE::Node>(pa);
        aScene->nodes[pNodeTmp->name]   = pNodeTmp.toWeakRef();

    } else if (eName == "matrix") {

        QVector<QVector4D> rows{};


        for (int index = 0; index < 4; ++index){
            
            float x,y,z,w;
            textString >> x; textString >> y; textString >> z; textString >> w;
            rows.push_back(QVector4D{x,y,z,w});

        }
        
        pNodeTmp->transform = QMatrix4x4{
            rows[0][0], rows[0][1], rows[0][2], rows[0][3],
            rows[1][0], rows[1][1], rows[1][2], rows[1][3],
            rows[2][0], rows[2][1], rows[2][2], rows[2][3],
            rows[3][0], rows[3][1], rows[3][2], rows[3][3]};

    } else if (pNodeTmp->nodeTypeMap.find(eName) != pNodeTmp->nodeTypeMap.end()){
        auto pUrlString     = attrMap["url"].toStdString();
        auto pUrl           = pUrlString.data() + 1;
        pNodeTmp->url       = QString{pUrl};
        pNodeTmp->nodeType  = pNodeTmp->nodeTypeMap[eName];

    } else if (eName == "instance_material") {

        auto symbol                 = attrMap["symbol"];
        auto target                 = QString{attrMap["target"].data() + 1};

        auto& urlmap = aScene->urlPtrMap;
        for ( auto urlmapiterator = urlmap.begin(); urlmapiterator != urlmap.end(); ++urlmapiterator){

            //Lookout for target
            auto url = urlmapiterator.key();
            if ( url != target ) continue;
            auto value = urlmapiterator.value();

            //Target found, create a new entry pointer to the same idname;
            aScene->urlPtrMap[symbol]    = value;

        }

    }

    return true;
}
//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace std;


QPair<QString, QPair<QString, QString>> QQE::ColladaVisitor::GetNameParentText(const QDomElement& e){

    auto parent = e.parentNode();
    auto elementName = e.nodeName();
    auto nodeText = e.text();
    auto parentName = parent.nodeName();
    auto parent_text = qMakePair(parentName, nodeText);
    auto node__parent_text = qMakePair(elementName, parent_text);

    return node__parent_text;

}

QString QQE::ColladaVisitor::GetElementText(const QDomElement& e){

    auto eText = e.text();
    auto eTextString = (eText.isEmpty()) ? QString{} : QString{eText} ;
    return eTextString;

}

QString QQE::ColladaVisitor::GetParentName(const QDomElement& e){

    //Get Parent dict
    auto parent = e.parentNode();
    return parent.nodeName();

}

bool QQE::ColladaVisitor::VisitEnter(const QDomElement& e, const QDomNamedNodeMap& pa){
    
    auto eName                      = e.nodeName();
    auto eNameSearchForVisitorState = stateMap.find(eName);
    auto eNameStateFound            = eNameSearchForVisitorState != stateMap.end();
    auto& visitorState              = visitorStateDqS.top();
    if  ( eNameStateFound ){

        auto& visitorStateName = eName;
        visitorStateDqS.push(stateMap[visitorStateName]);

    } else if (visitorState == ColladaVisitor::VisitorState::library_effects){

        return VisitEnter_library_effects(e, pa);

    } else if (visitorState == ColladaVisitor::VisitorState::library_images){

        return VisitEnter_library_images(e, pa);

    } else if (visitorState == ColladaVisitor::VisitorState::library_materials){

        return VisitEnter_library_materials(e, pa);

    } else if (visitorState == ColladaVisitor::VisitorState::library_geometries){

        return VisitEnter_library_geometries(e, pa);

    } else if (visitorState == ColladaVisitor::VisitorState::library_cameras){

        return VisitEnter_library_cameras(e, pa);

    } else if (visitorState == ColladaVisitor::VisitorState::library_lights){

        return VisitEnter_library_lights(e, pa);

    } else if (visitorState == ColladaVisitor::VisitorState::library_visual_scenes){

        return VisitEnter_library_visual_scenes(e, pa);

    } else if (eName == "authoring_tool") {

        aScene->authoring_tool = GetElementText(e);

    } else if (eName == "created") { 

        aScene->created = GetElementText(e);

    } else if (eName == "modified") { 

        aScene->modified = GetElementText(e);

    } else if (eName == "up_axis") {

        auto z_up = GetElementText(e);
        aScene->z_up = z_up == "Z_UP" ? true : false;

    } else if (visitorState == ColladaVisitor::VisitorState::newparam){

        return VisitEnter_newparam(e, pa);        

    }

     

    return true;
}

bool QQE::ColladaVisitor::VisitExit(const QDomElement& e){

    auto eName         = e.nodeName();
    auto& visitorState = visitorStateDqS.top();
    auto retValue      = true;

    if (visitorState == ColladaVisitor::VisitorState::library_geometries){

        retValue       = VisitExit_library_geometries(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_cameras){

        retValue       = VisitExit_library_cameras(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_images){

        retValue       = VisitExit_library_images(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_effects){

        retValue       = VisitExit_library_effects(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_lights){

        retValue       = VisitExit_library_lights(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_materials){

        retValue       = VisitExit_library_materials(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_visual_scenes){

        retValue       = VisitExit_library_visual_scenes(e);
    }

    auto eNameSearchForVisitorState = stateMap.find(eName);
    auto eNameStateFound            = eNameSearchForVisitorState != stateMap.end();

    if (eNameStateFound){

        visitorStateDqS.pop();

    }

    return retValue;
}
void QQE::ColladaVisitor::VisitNode(const QDomElement& pNode, int count = 0) {

    auto pNodeName = pNode.nodeName();

    auto msg = QString();
    for (auto index = 0; index < count; ++index) msg+=' ';
    qInfo() << msg+pNodeName;

    VisitEnter(pNode, pNode.attributes());
    auto child =  pNode.firstChildElement();
    count++;
    while (!child.isNull()){

        VisitNode(child, count);
        child = child.nextSiblingElement();

    }
    count--;
    VisitExit(pNode);
    if (!count){
        auto aScene = GetScene();
        auto& urlptrmap = aScene->urlPtrMap;
        for(auto urlptrmapit = urlptrmap.begin(); urlptrmapit != urlptrmap.end(); ++urlptrmapit){
            auto url = urlptrmapit.key();
            auto wp = urlptrmapit.value();
            auto sp = wp.lock();
            auto msg = QString{sp ? "[[Object available]]" : "**Object not available**"};
            msg = url + " => " + msg;
            qInfo() << msg;
        }
    }
}
void QQE::ColladaVisitor::LoadColladaDocument(QFile*p){

    QDomDocument xmlBOM;
    xmlBOM.setContent(p);
    p->close();

    auto root = xmlBOM.documentElement();
    VisitNode(root);

}


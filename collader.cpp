//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;

std::string GTech::ColladaVisitor::GetElementText(const XMLElement& e){

    auto eText = e.GetText();
    auto eTextString = (eText != nullptr) ? std::string{eText} : std::string{};
    return eTextString;

}

void GTech::ColladaVisitor::PrintSceneInfo(){

    std::cout << "\n";

    std::cout << "Exporting Tool: " << aScene.authoring_tool << std::endl;
    std::cout << "Created By    : " << aScene.created << std::endl;
    std::cout << "Modified      : " << aScene.modified << std::endl;
    
    
    /* List of nodes */
    std::cout << "\nNODE PTRS:\n";
    std::cout << "=====\n\n";

    for (auto& nodePtrName_nodePtr : nodePtrMap){

        auto nodePtrName = nodePtrName_nodePtr.first;
        auto nodePtr = nodePtrName_nodePtr.second;

        std::cout << "NAME: " << nodePtrName << " Add: 0x" << std::hex << (unsigned long)nodePtr << "\n";

    }

    /* List of nodes */
    std::cout << "\nNODES:\n";
    std::cout << "=====\n\n";
    
    for (auto& nodename_thenode : aScene.nodes){

        auto nodename   = nodename_thenode.first;
        auto node       = nodename_thenode.second;
        auto nodePtr    = nodePtrMap[node.url];
        std::cout << "Instance: " << node.instanceType << " NAME: " << nodename << " URL: " << node.url << ": 0x" << std::hex << (unsigned long)nodePtr << " \n";
        if (node.instanceType == "instance_camera"){
            auto cameraNode = dynamic_cast<GTech::Camera*>(nodePtr);
            cameraNode->Print();
        } else if (node.instanceType == "instance_light"){
            auto lightNode = dynamic_cast<GTech::Light*>(nodePtr);
            lightNode->Print();
        }
    }
    
    

    /* Print the tree */


}

bool GTech::ColladaVisitor::VisitEnter(const XMLElement& e, const XMLAttribute* pa){
    
    auto eName                      = std::string{e.Name()};
    auto eNameSearchForVisitorState = stateMap.find(eName);
    auto eNameStateFound            = eNameSearchForVisitorState != stateMap.end();
    

    if  ( eNameStateFound ){

        auto& visitorStateName = eName;
        visitorState = stateMap[visitorStateName];

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

        aScene.authoring_tool = GetElementText(e);

    } else if (eName == "created") { 

        aScene.created = GetElementText(e);

    } else if (eName == "modified") { 

        aScene.modified = GetElementText(e);

    } else if (eName == "up_axis") {

        auto z_up = GetElementText(e);
        aScene.z_up = z_up == "Z_UP" ? true : false;

    } 

     

    return true;
}

bool GTech::ColladaVisitor::VisitExit(const XMLElement& e){

    auto eName = std::string{e.Name()};

    if (visitorState == ColladaVisitor::VisitorState::library_geometries){

        return VisitExit_library_geometries(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_cameras){

        return VisitExit_library_cameras(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_images){

        return VisitExit_library_images(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_effects){

        return VisitExit_library_effects(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_lights){

        return VisitExit_library_lights(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_materials){

        return VisitExit_library_materials(e);

    } else if (visitorState == ColladaVisitor::VisitorState::library_visual_scenes){

        return VisitExit_library_visual_scenes(e);
    }

    return true;
}



int main (){

	XMLDocument doc;
	doc.LoadFile("../simple.dae");

    GTech::ColladaVisitor visitor;
    auto pVisitor = &visitor;
    doc.Accept(pVisitor);
    visitor.PrintSceneInfo();

	return 0;
}
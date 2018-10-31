//http://www.wazim.com/Collada_Tutorial_1.htm
#include "collader.h"


using namespace tinyxml2;
using namespace std;


std::tuple<std::string, std::string, const char*> GTech::ColladaVisitor::GetNameParentText(const tinyxml2::XMLElement& e){

    return std::make_tuple(std::string{e.Name()}, GetParentName(e), e.GetText());

}

std::string GTech::ColladaVisitor::GetElementText(const XMLElement& e){

    auto eText = e.GetText();
    auto eTextString = (eText != nullptr) ? std::string{eText} : std::string{};
    return eTextString;

}

std::string GTech::ColladaVisitor::GetParentName(const XMLElement &e){

    //Get Parent dict
    return std::string{reinterpret_cast<const tinyxml2::XMLElement*>(e.Parent())->Name()};

}

bool GTech::ColladaVisitor::VisitEnter(const XMLElement& e, const XMLAttribute* pa){
    
    auto eName                      = std::string{e.Name()};
    auto eNameSearchForVisitorState = stateMap.find(eName);
    auto eNameStateFound            = eNameSearchForVisitorState != stateMap.end();
    auto& visitorState              = visitorStateDq.front();


    if  ( eNameStateFound ){

        auto& visitorStateName = eName;
        visitorStateDq.push_front(stateMap[visitorStateName]) ;

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

    } else if (visitorState == ColladaVisitor::VisitorState::newparam){

        return VisitEnter_newparam(e, pa);        

    }

     

    return true;
}

bool GTech::ColladaVisitor::VisitExit(const XMLElement& e){

    auto eName         = std::string{e.Name()};
    auto& visitorState = visitorStateDq.front();
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

        visitorStateDq.pop_front();

    }

    return retValue;
}




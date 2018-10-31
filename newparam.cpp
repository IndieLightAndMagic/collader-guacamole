#include "newparam.h"
#include "collader.h"
#include <tuple>

using namespace tinyxml2;
using namespace std;

using namespace GTech;



GTech::NewParamPtr pNewParamTmp = nullptr;
void GTech::NewParam::SetIdName(const tinyxml2::XMLAttribute* pa){

    assert(pa != nullptr);
    id        = pa->Value();
    auto next = pa->Next();
    name      = next ? next->Value() : id;

}
bool GTech::ColladaVisitor::VisitEnter_newparam(const XMLElement& e, const XMLAttribute* pa){
    
    //std::string, std::string, char* 
    const auto& [eName, parentName, eText] = GetNameParentText(e);
    
    
    if (eName == "newparam") {

    }
    else if (eName == "surface") {
        
        //Get parent dicitionary.
        auto parent_e  = reinterpret_cast<const XMLElement*>(e.Parent());        
        auto parent_pa = parent_e->FirstAttribute();

        //Reset the actual pointer.
        pNewParamTmp.reset();
        
        //Create a new element use the surface XMLAttribute pointer.
        pNewParamTmp                          = CreateElement<GTech::Surface>(parent_pa);
        
        //Set the type
        aScene.parameters[pNewParamTmp->name] = pNewParamTmp;  
        pNewParamTmp->paramType               = GTech::NewParam::ParamType::SURFACE;

    } else if (eName == "sampler2D") {

        auto parent_e  = reinterpret_cast<const XMLElement*>(e.Parent());        
        auto parent_pa = parent_e->FirstAttribute();
        pNewParamTmp.reset();
        pNewParamTmp                          = CreateElement<GTech::Sampler2D>(parent_pa);
        aScene.parameters[pNewParamTmp->name] = pNewParamTmp;  
        pNewParamTmp->paramType               = GTech::NewParam::ParamType::SAMPLER2D;
        
    } else if (eName == "init_from") {

        auto pSurface       = std::dynamic_pointer_cast<GTech::Surface>(pNewParamTmp);
        pSurface->init_from = std::string{eText};

    } else if (eName == "format") {

        auto pSurface       = std::dynamic_pointer_cast<GTech::Surface>(pNewParamTmp);
        auto pComponentChar = eText;
        auto chartobase10 = [](auto& b10, auto& c){
            b10 = b10 * 0x0a + c - 0x30;
            return; 
        };

        std::map<char, std::function<void(unsigned char)>> parseDict {
            std::make_pair('A', [&](unsigned char bitsPerChannel){ 
                chartobase10(pSurface->format.r, bitsPerChannel);
            }),
            std::make_pair('R', [&](unsigned char bitsPerChannel){ 
                chartobase10(pSurface->format.g, bitsPerChannel);
            }),
            std::make_pair('G', [&](unsigned char bitsPerChannel){ 
                chartobase10(pSurface->format.b, bitsPerChannel);
            }),
            std::make_pair('B', [&](unsigned char bitsPerChannel){ 
                chartobase10(pSurface->format.a, bitsPerChannel);
            })
        };

        while (*pComponentChar){
            if (parseDict.find(*pComponentChar) != parseDict.end()){
                parseDict[*pComponentChar](*(pComponentChar+1));
            }
            pComponentChar++;
        }


    } else if (eName == "source") {

        auto pSampler2D = std::dynamic_pointer_cast<GTech::Sampler2D>(pNewParamTmp);
        pSampler2D->source = std::string{eText};

    }
    return true;    

}  
bool GTech::ColladaVisitor::VisitExit_newparam(const tinyxml2::XMLElement& e){


    return true;
}          
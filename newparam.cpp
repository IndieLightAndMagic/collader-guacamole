#include "newparam.h"
#include "collader.h"
#include <tuple>
#include <functional>

using namespace QQE;



QSharedPointer<QQE::NewParam> pNewParamTmp = nullptr;
void QQE::NewParam::SetIdName(const QDomNamedNodeMap& pa){

    id = pa.item(0).nodeValue();
    name = pa.length() > 1 ? pa.item(1).nodeValue() : id;

}

bool QQE::ColladaVisitor::VisitEnter_newparam(const QDomElement& e, const QDomNamedNodeMap& pa){
    
    //std::string, std::string, char* 
    //const auto& [eName, parentName, eText] = GetNameParentText(e);
    auto eName__parentName_eText = GetNameParentText(e);
    auto eName = eName__parentName_eText.first;
    auto parentName = eName__parentName_eText.second.first;
    auto eText = eName__parentName_eText.second.second;

    
    if (eName == "newparam") {

    }
    else if (eName == "surface") {
        
        //Get parent dicitionary.
        auto parent_e  = e.parentNode();
        auto parent_pa = parent_e.attributes();

        //Reset the actual pointer.
        pNewParamTmp.reset();
        
        //Create a new element use the surface XMLAttribute pointer.
        pNewParamTmp                          = CreateElement<QQE::Surface>(parent_pa);
        
        //Set the type
        aScene->parameters[pNewParamTmp->name] = pNewParamTmp.toWeakRef();
        pNewParamTmp->paramType                = QQE::NewParam::ParamType::SURFACE;

    } else if (eName == "sampler2D") {

        auto parent_e  = e.parentNode();
        auto parent_pa = parent_e.attributes();

        pNewParamTmp.reset();
        pNewParamTmp                           = CreateElement<QQE::Sampler2D>(parent_pa);
        aScene->parameters[pNewParamTmp->name] = pNewParamTmp.toWeakRef();
        pNewParamTmp->paramType                = QQE::NewParam::ParamType::SAMPLER2D;
        
    } else if (eName == "init_from") {

        auto pSurface = pNewParamTmp.dynamicCast<QQE::Surface>(); //std::dynamic_pointer_cast<QQE::Surface>(pNewParamTmp);
        if (pSurface == Q_NULLPTR){
            pNewParamTmp.reset();
            pSurface = QSharedPointer<QQE::Surface>::create();
            pNewParamTmp = pSurface;
        }
        pSurface->init_from = eText;

    } else if (eName == "format") {

        auto pSurface = pNewParamTmp.dynamicCast<QQE::Surface>();//std::dynamic_pointer_cast<QQE::Surface>(pNewParamTmp);
        if (pSurface == Q_NULLPTR){
            pNewParamTmp.reset();
            pSurface = QSharedPointer<QQE::Surface>::create();
            pNewParamTmp = pSurface;
        }
        auto pComponentChar = eText.toStdString().data();
        auto chartobase10 = [](auto& b10, auto& c){
            b10 = b10 * 0x0a + c - 0x30;
            return; 
        };

        QMap<char, std::function<void(unsigned char)>> parseDict {
            std::make_pair('A', [&](unsigned char bitsPerChannel){ 
                chartobase10(pSurface->format[0], bitsPerChannel);
            }),
            std::make_pair('R', [&](unsigned char bitsPerChannel){ 
                chartobase10(pSurface->format[1], bitsPerChannel);
            }),
            std::make_pair('G', [&](unsigned char bitsPerChannel){ 
                chartobase10(pSurface->format[2], bitsPerChannel);
            }),
            std::make_pair('B', [&](unsigned char bitsPerChannel){ 
                chartobase10(pSurface->format[3], bitsPerChannel);
            })
        };

        while (*pComponentChar){
            auto pComponentChar_ = *pComponentChar;

            if (parseDict.find(*pComponentChar) != parseDict.end()){
                parseDict[*pComponentChar](*(pComponentChar+1));
            }
            pComponentChar++;
        }


    } else if (eName == "source") {

        auto pSampler2D = pNewParamTmp.dynamicCast<QQE::Sampler2D>(); //std::dynamic_pointer_cast<QQE::Sampler2D>(pNewParamTmp);
        if (pSampler2D == Q_NULLPTR){
            pSampler2D = QSharedPointer<QQE::Sampler2D>::create();
        }
        pSampler2D->source = eText;

    }
    return true;    

}  
bool QQE::ColladaVisitor::VisitExit_newparam(const QDomElement& e){


    return true;
}          
#include "collader.h"

#include <Resourcer/resourcer.h>

#include <memory>


namespace GTech {

    using PXMLDoc = std::shared_ptr<tinyxml2::XMLDocument>;

    class ResourceManager : public GTech::Resourcer, public GTech::ColladaVisitor {

        ResourceManager() = default;

        /**
         * Map of names and scenes.
         */
        std::map<std::string, PXMLDoc> map_SResourceName_PXMLDoc;
        PXMLDoc GetPXMLDoc(const std::string& resourceName);
        
    public:
        unsigned int Load(const std::string& resourceName) override;
        void UnLoad(const std::string& resourceName) override;


        



        

    };

}
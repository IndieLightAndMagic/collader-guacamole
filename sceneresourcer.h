#include "collader.h"

#include <Resourcer/resourcer.h>

#include <tuple>
#include <memory>

/* Some definitions:
    - Resource Name is the Name of a resource.
    - Resource File is a File (usually a collada file) holding one or more resources.

    - Example of resourcename: Cube.
    - Example of resourcefile: ../Scene.dae.

*/
namespace GTech {

    using PairDocVisitor = std::pair<tinyxml2::XMLDocument, GTech::ColladaVisitor>;
    using PairDocVisitorPtr = std::shared_ptr<PairDocVisitor>;
    PairDocVisitorPtr make_PairDocVisitorPtr() {
        auto ptr = std::make_shared<PairDocVisitor>();
        return ptr; 
    }
    
    
    class ResourceManager : public GTech::Resourcer, public GTech::ColladaVisitor {

        ResourceManager() = default;

        /**
         * Map of names and shared ptrs to XMLDoc scenes.
         */
        std::map<std::string, PairDocVisitorPtr> map_SResourceName_PairDocVisitor;

        PairDocVisitorPtr GetPairDocVisitorPtr(const std::string& resourceFilenamePathStr);

        /**
         * @brief      Static resolution for asset integration. Suppose you have a foo.dae scene file and within it an object named "Cube". This private funciton will return a tuple of strings: ["scene.dae", "Cube"]. This function is inteded to be used within ResourceManager Class methods as it is private. 
         *
         * @param[in]  spath  The string path of the resource it could be something like ex1: "../scene.dae/Cube" or ex2: "../scene.dae" or ex3:"/Cube" and ex4:"Cube". 
         *
         * @return For ex1 if the file "../scene.dae" actually exists the returned tuple will be ["../scene.dae", "Cube"], if it doesn't ["","Cube"]. For ex2 whether it exists or not "../scene.dae" would be correspondently ["../scene.dae", ""], ["",""]. For ex3 and ex4 ["","Cube"]    
         */
        static std::tuple<std::string, std::string> ResourceNameResolution(const std::string& spath);

        /**
         * @brief      Check if a resource file is alredy registered.
         *
         * @param[in]  resourceFilenamePathStr  path to file to be checked if already registered.
         *
         * @return     If file is already registered on system true will be returnerd.
         */
        bool ResourceFileIsRegistered(const std::string& resourceFilenamePathStr);

        /**
         * @brief      Register the assets of a filename. It will register the file and preload the assets. 
         *
         * @param[in]  resourceFilenamePathStr  Path str to file with asset resources.        
         *
         * @return     On success will return true otherwise.... 
         */
        bool RegisterResource(const std::string& resourceFilenamePathStr);

        unsigned int LoadMesh(const GTech::Scene&, const GTech::Node&);
    public:
        unsigned int Load(const std::string& resourceName) override;
        void UnLoad(const std::string& resourceName) override;

        void ClearCache();

    };

}
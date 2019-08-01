
#include "collader.h"

#include <vector>
#include <map>

namespace QQE {

    struct NodeAccess{

        ssize_t bytesPerElement;
        unsigned int elementCount;
    
    };

    struct GlColladerScene {

        std::map<std::string, NodeAccess> nodeAccess;
        
    private:
        /**
         * Vertex data
         */
        std::vector<float> _vertexdata_;
        std::vector<float> _normaldata_;
        std::vector<float> _texcrddata_;


    };

}    
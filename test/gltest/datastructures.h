#include <vector>
#include <map>

namespace RenderingData {

    template <typename MatrixType>
    struct RenderData {

        using vectormatrix = std::vector<MatrixType>;
        using mapvaomatrix = std::map<unsigned int, vectormatrix>; 

        std::map<unsigned int, mapvaomatrix> mShaderVaoMatrix;
        
    };

};
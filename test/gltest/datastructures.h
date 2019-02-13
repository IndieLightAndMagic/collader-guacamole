#include <map>
#include <vector>
namespace RenderingData {

    template <typename MT>
    struct TmtxVector{
        std::vector<MT> tmtxVector{};
    };

    template <typename MT>
    struct VaoTmtxVector{
        std::map<unsigned int, TmtxVector<MT>> vaoTmtxVectorMap{};
    };

    template <typename MT>
    struct ProgramVao {
        std::map<unsigned int, VaoTmtxVector<MT>> programVaoMap{};
    };

};
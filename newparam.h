#ifndef __NEWPARAM_H__
#define __NEWPARAM_H__

#include "idname.h"

namespace QQE {

    struct NewParam : public QQE::IdName {
        enum class ParamType {
            SURFACE,
            SAMPLER2D
        };    
        ParamType paramType;
        virtual void SetIdName(const QDomNamedNodeMap& pa) override;
    };
    using NewParamPtr = QSharedPointer<NewParam>;
    
    struct Surface  : public QQE::NewParam {

        QString init_from{};
        QVector<int> format{0,0,0,0};
    
    };
    
    struct Sampler2D : public QQE::NewParam {

        QString source{};


    };
}



#endif

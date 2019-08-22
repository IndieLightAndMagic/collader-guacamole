#ifndef __IDNAME_H__
#define __IDNAME_H__


#include <QMap>
#include <QDomElement>
#include <QWeakPointer>


namespace QQE {
	
	struct IdName;

	using IdMap = QMap<QString, QWeakPointer<QQE::IdName>>;
    struct IdName {
        QString id;
        QString name;
        
        virtual void SetIdName(const QDomNamedNodeMap& e);
        
    };
    
}

#endif
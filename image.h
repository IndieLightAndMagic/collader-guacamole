#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <iostream>
#include <string>

#include "idname.h"

namespace QQE {

	struct Image : public IdName {

        std::string path{};
		
    };

}
#endif

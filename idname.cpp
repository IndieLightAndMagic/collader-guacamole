#include "idname.h"

using namespace GTech;
void IdName::SetIdName(const tinyxml2::XMLAttribute *pa){

	assert(pa != nullptr);
	if (pa) id = pa->Value();
	auto next = pa->Next();
	assert(next != nullptr);
	if (next) name = next->Value();

}
        

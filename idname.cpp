#include "idname.h"

using namespace QQE;
void IdName::SetIdName(const tinyxml2::XMLAttribute *pa){

	assert(pa != nullptr);
	id = pa->Value(); //Get Id Attribute
	auto next = pa->Next();
	assert(next != nullptr);
	if (next) name = next->Value(); //Get Name Attribute

}
        

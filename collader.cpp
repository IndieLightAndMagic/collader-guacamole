#include "tinyxml2/tinyxml2.h"

#include <iostream>

using namespace tinyxml2;
using namespace std;

class ColladaVisitor : public XMLVisitor {
    unsigned int tabLevel{0};
public:
    bool VisitEnter(const XMLElement& e, const XMLAttribute* pa)
    {
        auto ename = e.Name();
        auto text = e.GetText();
        if (!text) {
            for (auto index = 0; index < tabLevel; ++index) cout << "\t";
            std::cout << "+ " << ename << " :" << endl;
        }

        tabLevel++;
        return true;
    }
    bool VisitExit(const XMLElement& e)
    {
        auto ename = e.Name();
        for (auto index = 0; index < tabLevel; ++index) cout << "\t";
        auto text = e.GetText();
        if (text) cout << ename << " : " << text << endl;
        if (tabLevel) tabLevel--;
        return true;
    }
};
int main (){

	XMLDocument doc;
	doc.LoadFile("../simple.dae");

    ColladaVisitor visitor;
    auto pVisitor = &visitor;
    doc.Accept(pVisitor);

	return 0;
}
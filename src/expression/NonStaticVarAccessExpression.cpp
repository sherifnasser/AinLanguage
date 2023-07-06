#include "NonStaticVarAccessExpression.hpp"

NonStaticVarAccessExpression::NonStaticVarAccessExpression(
    int lineNumber,
    std::wstring varName,
    SharedIExpression inside
):
    IExpression(lineNumber,nullptr),
    varName(varName),
    inside(inside){}

std::vector<std::wstring> NonStaticVarAccessExpression::prettyPrint(){

    auto prints=std::vector<std::wstring>();
    auto lineNumStr=std::to_wstring(lineNumber);
    prints.push_back(L"NonStaticVarAccessExpression \'"+varName+L"\' at "+lineNumStr);

    auto insidePrints=inside->prettyPrint();
    
    insidePrints[0]=L"└──\033[1;33m"+insidePrints[0]+L"\033[0m";

    for(int i=1;i<insidePrints.size();i++){   
        insidePrints[i]=L"    "+insidePrints[i];
    }

    prints.insert(prints.end(),insidePrints.begin(),insidePrints.end());

    return prints;
}

SharedIValue NonStaticVarAccessExpression::evaluate() {
    
}

void NonStaticVarAccessExpression::check(SharedBaseScope checkScope) {
    
}

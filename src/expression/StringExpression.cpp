#include "StringExpression.hpp"
#include "ainio.hpp"
#define wcout std::wcout
#define endl std::endl

StringExpression::StringExpression(std::wstring &val):val(val){}

void StringExpression::print(std::wstring tabsize){
    wcout<<tabsize<<"StringExpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<val<<endl;
}

std::wstring StringExpression::evaluate(SharedScope evalScope){
    // TODO: evaluate ctrl chars
    return val.substr(1,val.size()-2);
}
#include "NumberExpression.hpp"

NumberExpression::NumberExpression(std::wstring &val):val(val){}

void NumberExpression::print(std::wstring tabsize){
    std::wcout<<tabsize<<"NumberExpression"<<std::endl;
    auto newtabsize=tabsize+L"\t";
    std::wcout<<newtabsize<<val<<std::endl;
}

std::wstring NumberExpression::evaluate(SharedScope evalScope){
    return val;
}
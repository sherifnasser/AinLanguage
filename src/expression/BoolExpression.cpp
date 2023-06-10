#include "BoolExpression.hpp"
#include "KeywordToken.hpp"
#define wcout std::wcout
#define endl std::endl

bool BoolExpression::boolFromStr(std::wstring s){
    return s==KeywordToken::TRUE.getVal();
}

std::wstring BoolExpression::strFromBool(bool b){
    return (b)?KeywordToken::TRUE.getVal():KeywordToken::FALSE.getVal();
}

BoolExpression::BoolExpression(std::wstring &val):val(val){}

void BoolExpression::print(std::wstring tabSize){
    wcout<<tabSize<<"BoolExpression"<<endl;
    auto newtabsize=tabSize+L"\t";
    wcout<<std::boolalpha<<newtabsize<<boolFromStr(val)<<endl;
}

std::wstring BoolExpression::evaluate(SharedScope evalScope){
    return val;
}
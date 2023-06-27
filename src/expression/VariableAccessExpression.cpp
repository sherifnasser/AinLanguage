#include "OldVariableAccessExpression.hpp"
#include "Scope.hpp"
#include "OldVariable.hpp"
#define wcout std::wcout
#define endl std::endl

OldVariableAccessExpression::OldVariableAccessExpression(std::wstring &name):name(name){}

void OldVariableAccessExpression::print(std::wstring tabsize){
    wcout<<tabsize<<"OldVariableAccessExpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<name<<endl;
}

std::wstring OldVariableAccessExpression::evaluate(SharedScope evalScope){
    auto var=evalScope->getVarByName(this->name);
    return var->getCurrentValue();
}
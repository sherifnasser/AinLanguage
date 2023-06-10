#include "VariableAccessExpression.hpp"
#include "Scope.hpp"
#include "Variable.hpp"
#define wcout std::wcout
#define endl std::endl

VariableAccessExpression::VariableAccessExpression(std::wstring &name):name(name){}

void VariableAccessExpression::print(std::wstring tabsize){
    wcout<<tabsize<<"VariableAccessExpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<name<<endl;
}

std::wstring VariableAccessExpression::evaluate(SharedScope evalScope){
    auto var=evalScope->getVarByName(this->name);
    return var->getCurrentValue();
}
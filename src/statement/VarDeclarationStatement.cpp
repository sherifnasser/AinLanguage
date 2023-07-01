#include "VarDeclarationStatement.hpp"
#include "IOldExpression.hpp"
#include "OldVariable.hpp"

VarDeclarationStatement::VarDeclarationStatement(SharedScope runScope,SharedOldVariable var,SharedIOldExpression ex)
:IOldStatement(runScope),var(var),ex(ex){
    auto exist=runScope->getVarByName(var->getName());
    if(exist!=nullptr){
        throw L"The OldVariable "+(var->getName())+L" is declared before.";
    }
}

void VarDeclarationStatement::run(){
    //std::wstring tab=L"";
    //ex->print(tab);
    if(ex!=nullptr){
        auto exval=ex->evaluate(runScope);
        var->setCurrentValue(exval);
    }
    runScope->getVars()->push_back(var);
}
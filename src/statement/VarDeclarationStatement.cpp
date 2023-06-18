#include "VarDeclarationStatement.hpp"
#include "IExpression.hpp"
#include "Variable.hpp"

VarDeclarationStatement::VarDeclarationStatement(SharedScope runScope,SharedVariable var,SharedIExpression ex)
:IStatement(runScope),var(var),ex(ex){
    auto exist=runScope->getVarByName(var->getName());
    if(exist!=nullptr){
        throw L"The Variable "+(var->getName())+L" is declared before.";
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
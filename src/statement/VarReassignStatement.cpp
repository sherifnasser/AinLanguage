#include "VarReassignStatement.hpp"
#include "IExpression.hpp"
#include "OldVariable.hpp"

VarReassignStatement::VarReassignStatement(SharedScope runScope,std::wstring varname,SharedIExpression ex)
:IStatement(runScope),varname(varname),ex(ex){}

void VarReassignStatement::run(){
    auto var=runScope->getVarByName(varname);
    auto exval=ex->evaluate(runScope);
    var->setCurrentValue(exval);
}
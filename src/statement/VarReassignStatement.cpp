#include "VarReassignStatement.hpp"
#include "IOldExpression.hpp"
#include "OldVariable.hpp"

VarReassignStatement::VarReassignStatement(SharedScope runScope,std::wstring varname,SharedIOldExpression ex)
:IOldStatement(runScope),varname(varname),ex(ex){}

void VarReassignStatement::run(){
    auto var=runScope->getVarByName(varname);
    auto exval=ex->evaluate(runScope);
    var->setCurrentValue(exval);
}
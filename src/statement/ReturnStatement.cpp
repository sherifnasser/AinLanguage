#include "ReturnStatement.hpp"
#include "BaseScope.hpp"
#include "FunScope.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "IExpression.hpp"
#include "UnexpectedTypeException.hpp"
#include "FunDecl.hpp"
#include "UnitExpression.hpp"
#include <memory>

ReturnStatement::ReturnStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression ex
):IStatement(lineNumber,runScope),ex(ex){}

void ReturnStatement::run(){
    auto funScope=BaseScope::getContainingFun(runScope);
    funScope->setReturnValue(ex->evaluate());
}

SharedIExpression ReturnStatement::getEx()const{
    return ex;
}
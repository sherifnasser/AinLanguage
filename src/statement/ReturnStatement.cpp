#include "ReturnStatement.hpp"
#include "IExpression.hpp"
#include "FunScope.hpp" // Should be added to enable casting

ReturnStatement::ReturnStatement(SharedFunScope runScope,SharedIExpression ex):IStatement(runScope),ex(ex){}

void ReturnStatement::run(){
    auto exval=ex->evaluate(runScope);
    SharedFunScope fScope=std::dynamic_pointer_cast<FunScope>(runScope);
    fScope->setReturnValue(exval);
}
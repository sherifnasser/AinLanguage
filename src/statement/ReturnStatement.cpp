#include "ReturnStatement.hpp"
#include "IOldExpression.hpp"
#include "OldFunScope.hpp" // Should be added to enable casting

ReturnStatement::ReturnStatement(SharedOldFunScope runScope,SharedIOldExpression ex):IOldStatement(runScope),ex(ex){}

void ReturnStatement::run(){
    auto exval=ex->evaluate(runScope);
    SharedOldFunScope fScope=std::dynamic_pointer_cast<OldFunScope>(runScope);
    fScope->setReturnValue(exval);
}
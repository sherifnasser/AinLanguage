#include "ExpressionStatement.hpp"
#include "IOldExpression.hpp"

ExpressionStatement::ExpressionStatement(SharedScope runScope, SharedIOldExpression ex)
:IOldStatement(runScope),ex(ex){}

void ExpressionStatement::run(){
    ex->evaluate(runScope);
}
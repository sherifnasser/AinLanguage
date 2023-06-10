#include "ExpressionStatement.hpp"
#include "IExpression.hpp"

ExpressionStatement::ExpressionStatement(SharedScope runScope, SharedIExpression ex)
:IStatement(runScope),ex(ex){}

void ExpressionStatement::run(){
    ex->evaluate(runScope);
}
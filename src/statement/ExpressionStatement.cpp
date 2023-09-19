#include "ExpressionStatement.hpp"
#include "StmListScope.hpp"
#include "IExpression.hpp"

ExpressionStatement::ExpressionStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression ex
)
: IStatement(lineNumber,runScope),ex(ex){}

void ExpressionStatement::run(){
    ex->evaluate();
}

SharedIExpression ExpressionStatement::getEx()const{
    return ex;
}
#include "ExpressionStatement.hpp"
#include "StmListScope.hpp"

ExpressionStatement::ExpressionStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression ex
)
: IStatement(lineNumber,runScope),ex(ex){}

void ExpressionStatement::check() {
    
}

void ExpressionStatement::run(){

}
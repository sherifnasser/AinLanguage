#include "ReturnStatement.hpp"
#include "FunScope.hpp"


ReturnStatement::ReturnStatement(
    int lineNumber,
    SharedFunScope funScope,
    SharedIExpression ex
):IStatement(lineNumber,funScope),ex(ex){}

void ReturnStatement::check(){
}

void ReturnStatement::run(){
}
#include "AssignStatement.hpp"
#include "StmListScope.hpp"

AssignStatement::AssignStatement(
    int lineNumber,
    SharedStmListScope runScope,
    std::shared_ptr<AssignExpression> ex,
    SharedIExpression newValEx
)
:IStatement(lineNumber,runScope),ex(ex),newValEx(newValEx){}

void AssignStatement::check(){
    
}

void AssignStatement::run(){

}
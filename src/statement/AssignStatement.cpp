#include "AssignStatement.hpp"
#include "StmListScope.hpp"

AssignStatement::AssignStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression left,
    SharedIExpression right
)
:IStatement(lineNumber,runScope),left(left),right(right){}

void AssignStatement::check(){
    
}

void AssignStatement::run(){

}
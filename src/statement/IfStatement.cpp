#include "IfStatement.hpp"
#include "StmListScope.hpp"

IfStatement::IfStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression ifCondition,
    SharedStmListScope ifScope,
    SharedStmListScope elseScope
)
    : IStatement(lineNumber,runScope),
      ifCondition(ifCondition),
      ifScope(ifScope),
      elseScope(elseScope)
{}

void IfStatement::check(){
    
}

void IfStatement::run(){
    
}

#include "ContinueStatement.hpp"
#include "LoopScope.hpp"

ContinueStatement::ContinueStatement(
    int lineNumber,
    SharedBaseScope runScope,
    SharedLoopScope loopScope
)
    : IStatement(lineNumber,runScope),
      loopScope(loopScope){}

void ContinueStatement::check(){}

void ContinueStatement::run(){
    loopScope->makeContinue();
}

#include "BreakStatement.hpp"
#include "LoopScope.hpp"

BreakStatement::BreakStatement(
    int lineNumber,
    SharedBaseScope runScope,
    SharedLoopScope loopScope
)
    : IStatement(lineNumber,runScope),
      loopScope(loopScope){}

void BreakStatement::run(){
    loopScope->makeBreak();
}
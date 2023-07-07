#include "DoWhileStatement.hpp"
#include "StmListScope.hpp"
#include "KeywordToken.hpp"

DoWhileStatement::DoWhileStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression condition,
    SharedStmListScope doWhileScope
)
    : IStatement(lineNumber,runScope),
      condition(condition),
      doWhileScope(doWhileScope)
{}

void DoWhileStatement::check(){

}

void DoWhileStatement::run(){

}
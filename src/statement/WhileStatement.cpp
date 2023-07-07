#include "WhileStatement.hpp"
#include "StmListScope.hpp"
#include "KeywordToken.hpp"

WhileStatement::WhileStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression condition,
    SharedStmListScope whileScope
)
    : IStatement(lineNumber,runScope),
      condition(condition),
      whileScope(whileScope)
{}

void WhileStatement::check(){

}

void WhileStatement::run(){

}
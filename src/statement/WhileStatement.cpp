#include "WhileStatement.hpp"
#include "BoolValue.hpp"
#include "StmListScope.hpp"
#include "KeywordToken.hpp"
#include "IExpression.hpp"
#include "Type.hpp"
#include "FunScope.hpp"
#include "semantics/UnexpectedTypeException.hpp"

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
    condition->check(runScope);

    if(condition->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *Type::BOOL_NAME,
            *condition->getReturnType()->getName()
        );
    
    whileScope->check();
}

void WhileStatement::run(){
    auto stmList=whileScope->getStmList();
    auto funScope=BaseScope::getContainingFun(runScope);
    while(condition->evaluateAs<BoolValue>()->getValue()){
        for(auto stm:*stmList){
            stm->run();
            if(funScope->getReturnValue())
                break;
        }
    }
}
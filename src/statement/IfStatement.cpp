#include "IfStatement.hpp"
#include "BoolValue.hpp"
#include "SharedPtrTypes.hpp"
#include "FunScope.hpp"
#include "IExpression.hpp"
#include "Type.hpp"
#include "semantics/UnexpectedTypeException.hpp"

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
    ifCondition->check(runScope);

    if(ifCondition->getReturnType()->getClassScope()!=Type::BOOL->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *Type::BOOL_NAME,
            *ifCondition->getReturnType()->getName()
        );
    
    ifScope->check();
    elseScope->check();
}

void IfStatement::run(){

    SharedStmList stmList;

    if(ifCondition->evaluateAs<BoolValue>()->getValue()){
        stmList=ifScope->getStmList();
    }
    else if(elseScope){
        stmList=elseScope->getStmList();
    }
    else return;
    
    auto funScope=BaseScope::getContainingFun(runScope);
    for(auto stm:*stmList){
        stm->run();
        if(funScope->getReturnValue())
            break;
    }
}

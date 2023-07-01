#include "IfStatement.hpp"
#include "IOldExpression.hpp"
#include "KeywordToken.hpp"
#include "OldFunScope.hpp" // Should be added to enable casting

IfStatement::IfStatement(
    SharedOldFunScope runScope,
    SharedIOldExpression ifCondition,
    SharedVector<SharedIOldStatement> ifStmList,
    SharedVector<SharedIOldStatement> elseStmList
):IOldStatement(runScope),
ifCondition(ifCondition),
ifStmList(ifStmList),
elseStmList(elseStmList)
{}

void IfStatement::run(){
    auto vars_size_before=runScope->getVars()->size();
    auto isIfConditionTrue=ifCondition->evaluate(runScope) == KeywordToken::TRUE.getVal();
    auto stmList=(isIfConditionTrue)?ifStmList:elseStmList;
    for(auto stm:*stmList){
        stm->run();
    }
    // pop all defined OldVariables in if statement
    runScope->getVars()->resize(vars_size_before);
}
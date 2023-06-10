#include "IfStatement.hpp"
#include "IExpression.hpp"
#include "KeywordToken.hpp"
#include "FunScope.hpp" // Should be added to enable casting

IfStatement::IfStatement(
    SharedFunScope runScope,
    SharedIExpression ifCondition,
    SharedVector<SharedIStatement> ifStmList,
    SharedVector<SharedIStatement> elseStmList
):IStatement(runScope),
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
    // pop all defined variables in if statement
    runScope->getVars()->resize(vars_size_before);
}
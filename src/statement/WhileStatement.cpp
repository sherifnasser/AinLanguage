#include "WhileStatement.hpp"
#include "IOldExpression.hpp"
#include "KeywordToken.hpp"
#include "OldFunScope.hpp" // Should be added to enable casting

WhileStatement::WhileStatement(
    SharedOldFunScope runScope,
    SharedIOldExpression ex,
    SharedVector<SharedIOldStatement> stmList
)
:IOldStatement(runScope),ex(ex),stmList(stmList){}

void WhileStatement::run(){

    auto vars_size_before=runScope->getVars()->size();

    while(ex->evaluate(runScope)==KeywordToken::TRUE.getVal()){ // while the condition is true
        for(auto stm:*stmList){
            stm->run();
        }
    }

    // pop all defined OldVariables in while IOldStatement
    runScope->getVars()->resize(vars_size_before);

}
#include "DoWhileStatement.hpp"
#include "IOldExpression.hpp"
#include "KeywordToken.hpp"
#include "OldFunScope.hpp" // Should be added to enable casting

DoWhileStatement::DoWhileStatement(
    SharedOldFunScope runScope,
    SharedIOldExpression ex,
    SharedVector<SharedIOldStatement> stmList
)
:WhileStatement(runScope,ex,stmList){}

void DoWhileStatement::run(){

    auto vars_size_before=runScope->getVars()->size();

    do{
        for(auto stm:*stmList){
            stm->run();
        }
    }while(ex->evaluate(runScope)==KeywordToken::TRUE.getVal());


    // pop all defined OldVariables in while IOldStatement
    runScope->getVars()->resize(vars_size_before);
}
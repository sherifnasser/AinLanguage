#include "WhileStatement.hpp"
#include "IExpression.hpp"
#include "KeywordToken.hpp"
#include "FunScope.hpp" // Should be added to enable casting

WhileStatement::WhileStatement(
    SharedFunScope runScope,
    SharedIExpression ex,
    SharedVector<SharedIStatement> stmList
)
:IStatement(runScope),ex(ex),stmList(stmList){}

void WhileStatement::run(){

    auto vars_size_before=runScope->getVars()->size();

    while(ex->evaluate(runScope)==KeywordToken::TRUE.getVal()){ // while the condition is true
        for(auto stm:*stmList){
            stm->run();
        }
    }

    // pop all defined variables in while IStatement
    runScope->getVars()->resize(vars_size_before);

}
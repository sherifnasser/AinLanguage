#include "statement.hpp"
#include "keywordtoken.hpp"

statement::statement(scope* runscope):runscope(runscope){}

expressionstatement::expressionstatement(scope* runscope, expression* ex)
:statement(runscope),ex(ex){}

void expressionstatement::run(){
    ex->evaluate(runscope);
}

vardeclarationstatement::vardeclarationstatement(scope* runscope,variable* var,expression* ex)
:statement(runscope),var(var),ex(ex){
    auto exist=runscope->getvarbyname(var->getname());
    if(exist!=nullptr){
        throw L"The variable "+(var->getname())+L" is declared before.";
    }
}

void vardeclarationstatement::run(){
    //std::wstring tab=L"";
    //ex->print(tab);
    if(ex!=nullptr){
        auto exval=ex->evaluate(runscope);
        var->setcurrentvalue(exval);
    }
    runscope->getvars()->push_back(var);
}

varreassignstatement::varreassignstatement(scope* runscope,std::wstring varname,expression* ex)
:statement(runscope),varname(varname),ex(ex){}

void varreassignstatement::run(){
    auto var=runscope->getvarbyname(varname);
    auto exval=ex->evaluate(runscope);
    var->setcurrentvalue(exval);
}

returnstatement::returnstatement(funscope* runscope,expression* ex):statement(runscope),ex(ex){}

void returnstatement::run(){
    auto exval=ex->evaluate(runscope);
    funscope* fscope=dynamic_cast<funscope*>(runscope);
    fscope->setreturnvalue(exval);
}

ifstatement::ifstatement(funscope* runscope,std::vector<ExStmList*>* exstmlists)
:statement(runscope),exstmlists(exstmlists){}

void ifstatement::run(){
    auto vars_size_before=runscope->getvars()->size();
    for(auto &exstmlist:*exstmlists){
        auto ex=exstmlist->first;  // condition
        auto stmlist=exstmlist->second; // then statements
        auto exval=ex->evaluate(runscope); // evaluate the condition
        if(exval==keywordtoken::TRUE.getval()){ // run then statements
            for(auto stm:*stmlist){
                stm->run();
            }
            // pop all defined variables in if statement
            runscope->getvars()->resize(vars_size_before);
            break; // don't evaluate next conditions
        }
    }   
}

whilestatement::whilestatement(funscope* runscope,expression* ex, StmList* stmlist)
:statement(runscope),ex(ex),stmlist(stmlist){}

void whilestatement::run(){

    auto vars_size_before=runscope->getvars()->size();

    while(ex->evaluate(runscope)==keywordtoken::TRUE.getval()){ // while the condition is true
        for(auto stm:*stmlist){
            stm->run();
        }
    }

    // pop all defined variables in while statement
    runscope->getvars()->resize(vars_size_before);

}
#include "statement.hpp"

statement::statement(scope* runscope):runscope(runscope){}

vardeclarationstatement::vardeclarationstatement(scope* runscope,variable* var,expression* ex)
:statement(runscope),var(var),ex(ex){
    auto exist=runscope->getvarbyname(var->getname());
    if(exist!=nullptr){
        throw L"The variable "+(var->getname())+L" is initialized before.";
    }
}

void vardeclarationstatement::run(){
    auto exval=ex->evaluate(runscope);
    var->setcurrentvalue(exval);
    runscope->getvars()->push_back(var);
}
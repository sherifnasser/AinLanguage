#include "statement.hpp"

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

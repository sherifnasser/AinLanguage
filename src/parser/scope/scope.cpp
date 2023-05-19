#include "scope.hpp"

wstring scope::getname(){
    return this->name;
}

void scope::setparentscope(scope* parentscope){
    this->parentscope=parentscope;
}

scope* scope::getparentscope(){
    return this->parentscope;
}

void scope::setvars(std::vector<variable>* vars){
    this->vars=vars;
}

std::vector<variable>* scope::getvars(){
    return this->vars;
}

void scope::setvals(std::vector<constant>* vals){
    this->vals=vals;
}

std::vector<constant>* scope::getvals(){
    return this->vals;
}

void scope::setfuns(std::vector<funscope>* funs){
    this->funs=funs;
}

std::vector<funscope>* scope::getfuns(){
    return this->funs;
}

void scope::setclasses(std::vector<classscope>* classes){
    this->classes=classes;
}

std::vector<classscope>* scope::getclasses(){
    return this->classes;
}

void funscope::init(){
    setvars(new std::vector<variable>());
    setvals(new std::vector<constant>());
}

funscope::funscope(wstring &name, wstring &returntype,std::vector<std::pair<wstring,wstring>>* args):returntype(returntype),args(args){
    this->name=name;
    init();
}

wstring funscope::getreturntype(){
    return this->returntype;
}

std::vector<std::pair<wstring,wstring>>* funscope::getargs(){
    return this->args;
}

variable::variable(scope* parentscope, wstring &name, wstring &type)
:parentscope(parentscope),name(name),type(type){}

constant::constant(scope* parentscope, wstring &name, wstring &type):
variable(parentscope,name,type){}

variable::variable(scope* parentscope, wstring &name, expression* ex)
:parentscope(parentscope),name(name),ex(ex){}

constant::constant(scope* parentscope, wstring &name, expression* ex):
variable(parentscope,name,ex){}

variable::variable(scope* parentscope, wstring &name, wstring &type, expression* ex)
:parentscope(parentscope),name(name),type(type),ex(ex){}

constant::constant(scope* parentscope, wstring &name, wstring &type, expression* ex):
variable(parentscope,name,type,ex){}

wstring variable::getname(){
    return this->name;
}

wstring variable::gettype(){
    return this->type;
}

expression* variable::getexpression(){
    return this->ex;
}
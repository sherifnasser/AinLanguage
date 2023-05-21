#include "scope.hpp"

scope::~scope(){}

std::wstring scope::getname(){
    return this->name;
}

void scope::setparentscope(scope* parentscope){
    this->parentscope=parentscope;
}

scope* scope::getparentscope(){
    return this->parentscope;
}

void scope::setvars(std::vector<variable*>* vars){
    this->vars=vars;
}

std::vector<variable*>* scope::getvars(){
    return this->vars;
}

void scope::setvals(std::vector<constant*>* vals){
    this->vals=vals;
}

std::vector<constant*>* scope::getvals(){
    return this->vals;
}

void scope::setfuns(std::vector<funscope*>* funs){
    this->funs=funs;
}

std::vector<funscope*>* scope::getfuns(){
    return this->funs;
}

void scope::setclasses(std::vector<classscope*>* classes){
    this->classes=classes;
}

std::vector<classscope*>* scope::getclasses(){
    return this->classes;
}

void funscope::setstmlist(std::vector<statement*>* stmlist){
    this->stmlist=stmlist;
}

std::vector<statement*>* funscope::getstmlist(){
    return this->stmlist;
}

void funscope::init(){
    setvars(new std::vector<variable*>());
    setvals(new std::vector<constant*>());
    setstmlist(new std::vector<statement*>());
}

funscope::funscope(scope* parentscope,std::wstring &name, std::wstring &returntype,std::vector<std::pair<std::wstring,std::wstring>>* args)
:returntype(returntype),args(args){
    this->setparentscope(parentscope);
    this->name=name;
    init();
}

std::wstring funscope::getreturntype(){
    return this->returntype;
}

std::wstring funscope::getreturnvalue(){
    return this->returnvalue;
}

std::vector<std::pair<std::wstring,std::wstring>>* funscope::getargs(){
    return this->args;
}

variable::variable(scope* parentscope, std::wstring &name, std::wstring &type)
:parentscope(parentscope),name(name),type(type){}

constant::constant(scope* parentscope, std::wstring &name, std::wstring &type):
variable(parentscope,name,type){}

std::wstring variable::getname(){
    return this->name;
}

std::wstring variable::gettype(){
    return this->type;
}

variable* scope::getvarbyname(std::wstring varname){
    for(auto &var:*getvars()){
        if(var->getname()==varname){
            return var;
        }
    }
    return nullptr;
}

funscope* scope::getfunbyname(std::wstring funname){
    for(auto &fun:*getfuns()){
        if(fun->getname()==funname){
            return fun;
        }
    }
    return nullptr;
}

std::wstring variable::getcurrentvalue(){
    if(isinitialized)
        return this->currentval;
    else{
        std::__throw_runtime_error("Variable is not initialized.");
    }
}

void variable::setcurrentvalue(std::wstring value){
    this->currentval=value;
    isinitialized=true;
}

void constant::setcurrentvalue(std::wstring value){
    if(isinitialized)
        std::__throw_runtime_error("Cannot reassign a constant value.");
    else
        variable::setcurrentvalue(value);
}

void funscope::call(){
    for(auto stm:*stmlist){
        stm->run();
        /*if(returnvalue!=nullptr)
            break;*/
    }
}

void funscope::setreturnvalue(std::wstring returnvalue){
    this->returnvalue=returnvalue;
}
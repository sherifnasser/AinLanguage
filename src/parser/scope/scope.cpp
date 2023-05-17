#include "scope.hpp"

scope::~scope(){}

wstring scope::getname(){
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

funscope::funscope(scope* parentscope,wstring &name, wstring &returntype,std::vector<std::pair<wstring,wstring>>* args)
:returntype(returntype),args(args){
    this->setparentscope(parentscope);
    this->name=name;
    init();
}

wstring funscope::getreturntype(){
    return this->returntype;
}

wstring funscope::getreturnvalue(){
    return this->returnvalue;
}

std::vector<std::pair<wstring,wstring>>* funscope::getargs(){
    return this->args;
}

variable::variable(scope* parentscope, wstring &name, wstring &type)
:parentscope(parentscope),name(name),type(type){}

constant::constant(scope* parentscope, wstring &name, wstring &type):
variable(parentscope,name,type){}

wstring variable::getname(){
    return this->name;
}

wstring variable::gettype(){
    return this->type;
}

variable* scope::getvarbyname(wstring varname){
    for(auto &var:*getvars()){
        if(var->getname()==varname){
            return var;
        }
    }
    return nullptr;
}

funscope* scope::getfunbyname(wstring funname){
    for(auto &fun:*getfuns()){
        if(fun->getname()==funname){
            return fun;
        }
    }
    return nullptr;
}

wstring variable::getcurrentvalue(){
    if(isinitialized)
        return this->currentval;
    else{
        std::__throw_runtime_error("Variable is not initialized.");
    }
}

void variable::setcurrentvalue(wstring value){
    this->currentval=value;
    isinitialized=true;
}

void constant::setcurrentvalue(wstring value){
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

void funscope::setreturnvalue(wstring returnvalue){
    this->returnvalue=returnvalue;
}
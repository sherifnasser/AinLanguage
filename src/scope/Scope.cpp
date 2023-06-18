#include "Scope.hpp"
#include "FunScope.hpp"
#include "Variable.hpp"

Scope::~Scope(){}

std::wstring Scope::getName(){
    return this->name;
}

void Scope::setParentScope(SharedScope parentScope){
    this->parentScope=parentScope;
}

SharedScope Scope::getparentScope(){
    return this->parentScope;
}

void Scope::setVars(SharedVector<SharedVariable> vars){
    this->vars=vars;
}

SharedVector<SharedVariable> Scope::getVars(){
    return this->vars;
}

void Scope::setVals(SharedVector<SharedConstant> vals){
    this->vals=vals;
}

SharedVector<SharedConstant> Scope::getVals(){
    return this->vals;
}

void Scope::setFuns(SharedVector<SharedFunScope> funs){
    this->funs=funs;
}

SharedVector<SharedFunScope> Scope::getFuns(){
    return this->funs;
}

void Scope::setClasses(SharedVector<SharedClassScope> classes){
    this->classes=classes;
}

SharedVector<SharedClassScope> Scope::getClasses(){
    return this->classes;
}

SharedVariable Scope::getVarByName(std::wstring varname){
    for(auto &var:*getVars()){
        if(var->getName()==varname){
            return var;
        }
    }
    return nullptr;
}

SharedFunScope Scope::getFunByName(std::wstring funName){
    for(auto &fun:*getFuns()){
        if(fun->getName()==funName){
            return fun;
        }
    }
    return nullptr;
}
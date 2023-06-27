#include "Scope.hpp"
#include "OldFunScope.hpp"
#include "OldVariable.hpp"

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

void Scope::setVars(SharedVector<SharedOldVariable> vars){
    this->vars=vars;
}

SharedVector<SharedOldVariable> Scope::getVars(){
    return this->vars;
}

void Scope::setVals(SharedVector<SharedOldConstant> vals){
    this->vals=vals;
}

SharedVector<SharedOldConstant> Scope::getVals(){
    return this->vals;
}

void Scope::setFuns(SharedVector<SharedOldFunScope> funs){
    this->funs=funs;
}

SharedVector<SharedOldFunScope> Scope::getFuns(){
    return this->funs;
}

void Scope::setClasses(SharedVector<SharedClassScope> classes){
    this->classes=classes;
}

SharedVector<SharedClassScope> Scope::getClasses(){
    return this->classes;
}

SharedOldVariable Scope::getVarByName(std::wstring varname){
    for(auto &var:*getVars()){
        if(var->getName()==varname){
            return var;
        }
    }
    return nullptr;
}

SharedOldFunScope Scope::getFunByName(std::wstring funName){
    for(auto &fun:*getFuns()){
        if(fun->getName()==funName){
            return fun;
        }
    }
    return nullptr;
}
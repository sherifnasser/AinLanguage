#include "scope.hpp"

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


funscope::funscope(wstring &name, wstring &returntype,std::map<wstring,wstring>* args):returntype(returntype),args(args){
    this->name=name;
}
funscope::funscope(wstring &name, std::map<wstring,wstring>* args):args(args){
    this->name=name;
}
funscope::funscope(wstring &name, wstring &returntype):returntype(returntype){
    this->name=name;
}
funscope::funscope(wstring &name){
    this->name=name;
}

#include "GlobalScope.hpp"

GlobalScope::GlobalScope(){
    this->funs=std::make_shared<std::vector<SharedFunScope>>();
}

void GlobalScope::addfunction(SharedFunScope funScope){
    getFuns()->push_back(funScope);
}

SharedFunScope GlobalScope::getmain(){
    auto fun=getFunByName(L"البداية");
    if(fun==nullptr)
        std::__throw_runtime_error("Couldn't find the main function");
    return fun;
}
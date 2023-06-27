#include "GlobalScope.hpp"
#include "MainFunctionNotFoundException.hpp"

GlobalScope::GlobalScope(){
    this->funs=std::make_shared<std::vector<SharedOldFunScope>>();
}

void GlobalScope::addfunction(SharedOldFunScope funScope){
    getFuns()->push_back(funScope);
}

SharedOldFunScope GlobalScope::getMain(){
    auto fun=getFunByName(L"البداية");
    if(fun==nullptr)
        throw MainFunctionNotFoundException();
    return fun;
}
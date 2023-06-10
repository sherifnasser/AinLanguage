#include "FunScope.hpp"
#include "IStatement.hpp"

FunScope::FunScope(
    SharedScope parentScope,
    std::wstring &name,
    std::wstring &returnType,
    SharedVector<std::pair<std::wstring,std::wstring>> args
)
:returnType(returnType),args(args){
    this->setParentScope(parentScope);
    this->name=name;
    this->vars=std::make_shared<std::vector<SharedVariable>>();
    this->vals=std::make_shared<std::vector<SharedConstant>>();
    this->stmList=std::make_shared<std::vector<SharedIStatement>>();
}


std::wstring FunScope::getReturnType(){
    return this->returnType;
}

std::wstring FunScope::getReturnValue(){
    return this->returnValue;
}

SharedVector<std::pair<std::wstring,std::wstring>> FunScope::getArgs(){
    return this->args;
}

void FunScope::setReturnValue(std::wstring returnValue){
    this->returnValue=returnValue;
}

SharedVector<SharedIStatement> FunScope::getStmList(){
    return this->stmList;
}

void FunScope::setStmList(SharedVector<SharedIStatement> stmList){
    this->stmList=stmList;
}

void FunScope::call(){
    for(auto stm:*stmList){
        stm->run();
        /*if(returnvalue!=nullptr)
            break;*/
    }
}


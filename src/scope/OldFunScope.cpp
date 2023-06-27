#include "OldFunScope.hpp"
#include "IStatement.hpp"

OldFunScope::OldFunScope(
    SharedScope parentScope,
    std::wstring &name,
    std::wstring &returnType,
    SharedVector<std::pair<std::wstring,std::wstring>> args
)
:returnType(returnType),args(args){
    this->setParentScope(parentScope);
    this->name=name;
    this->vars=std::make_shared<std::vector<SharedOldVariable>>();
    this->vals=std::make_shared<std::vector<SharedOldConstant>>();
    this->stmList=std::make_shared<std::vector<SharedIStatement>>();
}


std::wstring OldFunScope::getReturnType(){
    return this->returnType;
}

std::wstring OldFunScope::getReturnValue(){
    return this->returnValue;
}

SharedVector<std::pair<std::wstring,std::wstring>> OldFunScope::getArgs(){
    return this->args;
}

void OldFunScope::setReturnValue(std::wstring returnValue){
    this->returnValue=returnValue;
}

SharedVector<SharedIStatement> OldFunScope::getStmList(){
    return this->stmList;
}

void OldFunScope::setStmList(SharedVector<SharedIStatement> stmList){
    this->stmList=stmList;
}

void OldFunScope::call(){
    for(auto stm:*stmList){
        stm->run();
        /*if(returnvalue!=nullptr)
            break;*/
    }
}


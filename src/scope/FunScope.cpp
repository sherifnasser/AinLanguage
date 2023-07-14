#include "FunScope.hpp"
#include "FunDecl.hpp"
#include "SharedPtrTypes.hpp"
#include "FunParam.hpp"
#include "StmListScope.hpp"
#include "Variable.hpp"
#include "IStatement.hpp"
#include "FunDecl.hpp"
#include <string>

FunScope::FunScope(
    SharedBaseScope parentScope,
    SharedFunDecl decl
):StmListScope(*decl->name,parentScope),decl(decl)
{}

SharedIValue FunScope::invoke(SharedMap<std::wstring, SharedIValue> params){

    for(auto local:*locals){
        auto varName=local.first;
        auto var=local.second;
        var->pushNewValue();
        auto paramIt=params->find(varName);
        if(paramIt!=params->end()){
            var->setValue(paramIt->second);
        }
    }

    for(auto stm:*stmList){
        stm->run();
        if(this->returnValue)
            break;
    }

    for(auto local:*locals){
        local.second->popLastValue();
    }

    return this->returnValue;
}

SharedType FunScope::getReturnType(){
    return this->decl->returnType;
}

SharedFunDecl FunScope::getDecl(){
    return this->decl;
}

void FunScope::setReturnValue(SharedIValue returnValue){
    this->returnValue=returnValue;
}

SharedIValue FunScope::getReturnValue(){
    return this->returnValue;
}

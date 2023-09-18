#include "ConstructorScope.hpp"
#include "ClassScope.hpp"
#include "FunDecl.hpp"
#include "Type.hpp"
#include "Variable.hpp"
#include "IStatement.hpp"
#include "ObjectValue.hpp"

ConstructorScope::ConstructorScope(
    SharedFunDecl decl
):FunScope(decl->returnType->getClassScope(),decl)
{}

SharedIValue ConstructorScope::invoke(SharedMap<std::wstring, SharedIValue> params){
    
    // TODO: Primary constructor with parameters
    decl->returnType->getClassScope()->runPrimaryConstructor();

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

    this->returnValue=nullptr;

    auto properties=decl->returnType->getClassScope()->popLastProperties();
    
    return std::make_shared<ObjectValue>(decl->returnType,properties);
}

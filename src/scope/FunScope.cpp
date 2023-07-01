#include "FunScope.hpp"
#include "FunDecl.hpp"
#include "SharedPtrTypes.hpp"
#include "FunParamater.hpp"
#include "Variable.hpp"
#include "IStatement.hpp"

FunScope::FunScope(
    SharedBaseScope parentScope,
    SharedFunDecl decl,
    std::map<SharedWString, SharedVariable> locals,
    SharedVector<SharedIStatement> stmList
)
:BaseScope(*decl->name,parentScope)
,decl(decl),locals(locals),stmList(stmList)
{}

void FunScope::check(){
    this->returnType=getClassByType(decl->returnType);
    
    for(auto param:*decl->params){
        auto paramType=getClassByType(param->type);
        locals[param->name]->setType(paramType);
    }

    for(auto stm:*stmList){
        stm->check();
    }
}

SharedIValue FunScope::invoke(std::map<SharedWString, SharedIValue> params) {
    // TODO
    return nullptr;
}

SharedClassScope FunScope::getReturnType(){
    return returnType;
}

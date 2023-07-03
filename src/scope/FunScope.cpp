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

void FunScope::check(){
    
    for(auto stm:*stmList){
        stm->check();
    }
}

SharedIValue FunScope::invoke(std::map<std::wstring, SharedIValue> params){
    
    // TODO
    return nullptr;
}

SharedType FunScope::getReturnType(){
    return this->decl->returnType;
}
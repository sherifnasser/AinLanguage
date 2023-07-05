#include "StmListScope.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>
#include <vector>

StmListScope::StmListScope(std::wstring name,SharedBaseScope parentScope)
:
    BaseScope(name,parentScope),
    locals(
        std::make_shared<std::map<std::wstring,SharedVariable>>()
    ),
    stmList(
        std::make_shared<std::vector<SharedIStatement>>()
    )
{}

SharedMap<std::wstring, SharedVariable> StmListScope::getLocals(){
    return locals;
}

SharedVariable StmListScope::getVarByName(std::wstring varName){
    auto varIterator=locals->find(varName);
    if(varIterator==locals->end())
        return nullptr;
    return varIterator->second;
}

SharedVariable StmListScope::getLocalByName(std::wstring varName){

    SharedVariable var=getVarByName(varName);

    if(var)
        return var;

    auto stmListScope=std::dynamic_pointer_cast<StmListScope>(getParentScope());

    if(stmListScope)
        var=stmListScope->getLocalByName(varName);
    
    return var;
}

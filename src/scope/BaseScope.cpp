#include "BaseScope.hpp"

BaseScope::BaseScope(std::wstring name,SharedBaseScope parentScope)
:name(name),parentScope(parentScope){}

SharedBaseScope BaseScope::getParentScope() {
    return this->parentScope;
}

std::wstring BaseScope::getName() {
    return this->name;
}

BaseScope::~BaseScope(){}
SharedClassScope BaseScope::getClassByType(SharedType type){
    return getParentScope()->getClassByType(type);
}

SharedVariable BaseScope::getVarByName(std::wstring varName) {
    return getParentScope()->getVarByName(varName);
}

SharedVariable BaseScope::getFunByDecl(SharedFunDecl funDecl) {
    return getParentScope()->getFunByDecl(funDecl);
}

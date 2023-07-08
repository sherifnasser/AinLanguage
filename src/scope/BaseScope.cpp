#include "BaseScope.hpp"
#include "ClassScope.hpp"
#include "FileScope.hpp"
#include "FunScope.hpp"
#include "PackageScope.hpp"
#include "SharedPtrTypes.hpp"
#include "StmListScope.hpp"
#include <memory>

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

SharedFunScope BaseScope::toFunScope(SharedBaseScope scope){
    return std::dynamic_pointer_cast<FunScope>(scope);
}

SharedClassScope BaseScope::toClassScope(SharedBaseScope scope){
    return std::dynamic_pointer_cast<ClassScope>(scope);
}

SharedFileScope BaseScope::toFileScope(SharedBaseScope scope) {
    return std::dynamic_pointer_cast<FileScope>(scope);
}

SharedPackageScope BaseScope::toPackageScope(SharedBaseScope scope) {
    return std::dynamic_pointer_cast<PackageScope>(scope);
}

SharedFunScope BaseScope::getContainingFun(SharedBaseScope scope){

    while(scope){
        auto funScope=toFunScope(scope);
        if(funScope)
            return funScope;
        scope=scope->parentScope;
    }
    
    return nullptr;

}

SharedClassScope BaseScope::getContainingClass(SharedBaseScope scope){

    while(scope){
        auto classScope=toClassScope(scope);
        if(classScope)
            return classScope;
        scope=scope->parentScope;
    }
    
    return nullptr;
}

SharedFileScope BaseScope::getContainingFile(SharedBaseScope scope){

    while(scope){
        auto fileScope=toFileScope(scope);
        if(fileScope)
            return fileScope;
        scope=scope->parentScope;
    }
    
    return nullptr;
}

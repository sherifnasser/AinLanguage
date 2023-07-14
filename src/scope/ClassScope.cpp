#include "ClassScope.hpp"
#include <map>
#include <memory>

ClassScope::ClassScope(std::wstring name,SharedBaseScope parentScope)
    :BaseScope(name,parentScope),
    publicFunctions(std::make_shared<std::map<std::wstring,SharedFunScope>>()),
    privateFunctions(std::make_shared<std::map<std::wstring,SharedFunScope>>()),
    publicClasses(std::make_shared<std::map<std::wstring,SharedClassScope>>()),
    privateClasses(std::make_shared<std::map<std::wstring,SharedClassScope>>()),
    publicVariables(std::make_shared<std::map<std::wstring,SharedVariable>>()),
    privateVariables(std::make_shared<std::map<std::wstring,SharedVariable>>())
{
    
}

SharedMap<std::wstring,SharedFunScope> ClassScope::getPublicFunctions()const{
    return this->publicFunctions;
}

SharedMap<std::wstring,SharedFunScope> ClassScope::getPrivateFunctions()const{
    return this->privateFunctions;
}

SharedMap<std::wstring,SharedClassScope> ClassScope::getPublicClasses()const{
    return this->publicClasses;
}

SharedMap<std::wstring,SharedClassScope> ClassScope::getPrivateClasses()const{
    return this->privateClasses;
}

SharedFunScope ClassScope::findPublicFunction(std::wstring decl){
    auto funIterator=publicFunctions->find(decl);

    if(funIterator!=publicFunctions->end())
        return funIterator->second;
    
    return nullptr;
}

SharedFunScope ClassScope::findPrivateFunction(std::wstring decl){
    auto funIterator=privateFunctions->find(decl);

    if(funIterator!=privateFunctions->end())
        return funIterator->second;
        
    return nullptr;
}

SharedVariable ClassScope::findPublicVariable(std::wstring varName){
    auto varIterator=publicVariables->find(varName);

    if(varIterator!=publicVariables->end())
        return varIterator->second;
    
    return nullptr;
}

SharedVariable ClassScope::findPrivateVariable(std::wstring varName){
    auto varIterator=privateVariables->find(varName);

    if(varIterator!=privateVariables->end())
        return varIterator->second;
    
    return nullptr;
}
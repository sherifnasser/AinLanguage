#include "ClassScope.hpp"
#include "FunScope.hpp"
#include "ConstructorScope.hpp"
#include "SharedPtrTypes.hpp"
#include "StmListScope.hpp"
#include "IStatement.hpp"
#include "Variable.hpp"
#include <map>
#include <memory>
#include <string>

ClassScope::ClassScope(std::wstring name,SharedBaseScope parentScope)
    :BaseScope(name,parentScope),
    publicFunctions(std::make_shared<std::map<std::wstring,SharedFunScope>>()),
    privateFunctions(std::make_shared<std::map<std::wstring,SharedFunScope>>()),
    publicConstructors(std::make_shared<std::map<std::wstring,SharedConstructorScope>>()),
    privateConstructors(std::make_shared<std::map<std::wstring,SharedConstructorScope>>()),
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

SharedMap<std::wstring,SharedConstructorScope> ClassScope::getPublicConstructors() const {
    return this->publicConstructors;
}

SharedMap<std::wstring,SharedConstructorScope> ClassScope::getPrivateConstructors() const {
    return this->privateConstructors;
}

SharedMap<std::wstring,SharedClassScope> ClassScope::getPublicClasses()const{
    return this->publicClasses;
}

SharedMap<std::wstring,SharedClassScope> ClassScope::getPrivateClasses()const{
    return this->privateClasses;
}

SharedMap<std::wstring,SharedVariable> ClassScope::getPublicVariables()const{
    return this->publicVariables;
}

SharedMap<std::wstring,SharedVariable> ClassScope::getPrivateVariables()const{
    return this->privateVariables;
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

SharedConstructorScope ClassScope::findPublicConstructor(std::wstring decl) {
    auto constructorIterator=publicConstructors->find(decl);

    if(constructorIterator!=publicConstructors->end())
        return constructorIterator->second;
    
    return nullptr;
}

SharedConstructorScope ClassScope::findPrivateConstructor(std::wstring decl) {
    auto constructorIterator=privateConstructors->find(decl);

    if(constructorIterator!=privateConstructors->end())
        return constructorIterator->second;
    
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

SharedStmListScope ClassScope::getVarsInitStmList()const{
    return this->varsInitStmList;
}

void ClassScope::setVarsInitStmList(SharedStmListScope varsInitStmList){
    this->varsInitStmList=varsInitStmList;
}

void ClassScope::runVarsInitStmList(){

    pushNewProperties();

    auto stmList=varsInitStmList->getStmList();

    for(auto stm:*stmList){
        stm->run();
    }
}

void ClassScope::pushNewProperties(){
    for(auto varIt:*privateVariables){
        varIt.second->pushNewValue();
    }
    for(auto varIt:*publicVariables){
        varIt.second->pushNewValue();
    }
}

SharedMap<std::wstring, SharedIValue> ClassScope::popLastProperties(){
    
    auto properties=std::make_shared<std::map<std::wstring, SharedIValue>>();
    for(auto varIt:*privateVariables){
        (*properties)[varIt.first]=varIt.second->getValue();
        varIt.second->popLastValue();
    }
    for(auto varIt:*publicVariables){
        (*properties)[varIt.first]=varIt.second->getValue();
        varIt.second->popLastValue();
    }

    return properties;
}
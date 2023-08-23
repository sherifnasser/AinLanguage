#include "ObjectValue.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "FunScope.hpp"
#include "ClassScope.hpp"
#include "Variable.hpp"
#include <memory>

ObjectValue::ObjectValue(SharedType type,SharedMap<std::wstring, SharedIValue> properties)
:IValue(type),
properties(properties){}

void ObjectValue::linkWithClass(){
    auto privateVars=type->getClassScope()->getPrivateVariables();
    auto publicVars=type->getClassScope()->getPublicVariables();

    for(auto varIt:*privateVars){
        auto varName=varIt.first;
        auto var=varIt.second;
        var->pushNewValue();
        var->setValue((*properties)[varName]);
    }

    for(auto varIt:*publicVars){
        auto varName=varIt.first;
        auto var=varIt.second;
        var->pushNewValue();
        var->setValue((*properties)[varName]);
    }
}

void ObjectValue::unlinkWithClass(){
    auto privateVars=type->getClassScope()->getPrivateVariables();
    auto publicVars=type->getClassScope()->getPublicVariables();

    for(auto varIt:*privateVars){
        auto varName=varIt.first;
        auto var=varIt.second;
        (*properties)[varName]=var->getValue();
        var->popLastValue();
    }
    
    for(auto varIt:*publicVars){
        auto varName=varIt.first;
        auto var=varIt.second;
        (*properties)[varName]=var->getValue();
        var->popLastValue();
    }
}

std::wstring ObjectValue::toString(){
    return *type->getName();
}

SharedIValue ObjectValue::findPropertyValue(std::wstring propertyName){
    auto propertyIt=properties->find(propertyName);
    if(propertyIt!=properties->end())
        return propertyIt->second;
    return nullptr;
}

void ObjectValue::assignProperty(std::wstring propertyName,SharedIValue value){
    properties->at(propertyName)=value;
}

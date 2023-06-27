#include"OldVariable.hpp"

OldVariable::OldVariable(SharedScope parentScope, std::wstring &name, std::wstring &type)
:parentScope(parentScope),name(name),type(type){}

std::wstring OldVariable::getName(){
    return this->name;
}

std::wstring OldVariable::getType(){
    return this->type;
}

std::wstring OldVariable::getCurrentValue(){
    if(isInitialized)
        return this->currentVal;
    else{
        std::__throw_runtime_error("OldVariable is not initialized.");
    }
}

void OldVariable::setCurrentValue(std::wstring value){
    this->currentVal=value;
    isInitialized=true;
}
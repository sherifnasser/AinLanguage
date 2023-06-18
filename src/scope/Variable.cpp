#include"Variable.hpp"

Variable::Variable(SharedScope parentScope, std::wstring &name, std::wstring &type)
:parentScope(parentScope),name(name),type(type){}

std::wstring Variable::getName(){
    return this->name;
}

std::wstring Variable::getType(){
    return this->type;
}

std::wstring Variable::getCurrentValue(){
    if(isInitialized)
        return this->currentVal;
    else{
        std::__throw_runtime_error("Variable is not initialized.");
    }
}

void Variable::setCurrentValue(std::wstring value){
    this->currentVal=value;
    isInitialized=true;
}
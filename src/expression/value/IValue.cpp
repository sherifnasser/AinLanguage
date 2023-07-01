#include "SharedPtrTypes.hpp"
#include "IValue.hpp"

IValue::IValue(SharedClassScope type):type(type){}

SharedClassScope IValue::getType(){
    return this->type;
}

IValue::~IValue(){}
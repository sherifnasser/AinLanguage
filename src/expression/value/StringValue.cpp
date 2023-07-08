#include "StringValue.hpp"
#include "Type.hpp"

StringValue::StringValue(std::wstring value)
:IValue(Type::STRING),value(value){}

void StringValue::linkWithClass() {
    
}

std::wstring StringValue::toString() {
    return this->value;
}
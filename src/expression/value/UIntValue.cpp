#include "UIntValue.hpp"
#include "Type.hpp"

UIntValue::UIntValue(unsigned int value)
:PrimitiveValue(Type::UINT,value){}

std::wstring UIntValue::toString(){
    return std::to_wstring(value);
}
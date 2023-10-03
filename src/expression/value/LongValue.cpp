#include "LongValue.hpp"
#include "Type.hpp"

LongValue::LongValue(long long value)
:PrimitiveValue(Type::LONG,value){}

std::wstring LongValue::toString(){
    return std::to_wstring(value);
}
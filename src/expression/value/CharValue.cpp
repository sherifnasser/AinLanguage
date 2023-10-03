#include "CharValue.hpp"
#include "Type.hpp"
#include <string>

CharValue::CharValue(wchar_t value)
:PrimitiveValue(Type::CHAR,value){}

std::wstring CharValue::toString(){
    std::wstring val=L"";
    val+=value;
    return val;
}
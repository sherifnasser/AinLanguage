#include "CharValue.hpp"
#include "Type.hpp"

CharValue::CharValue(wchar_t value)
    : PrimitiveValue(Type::CHAR,value)
{
    
}

void CharValue::linkWithClass() {
    
}

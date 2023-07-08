#include "BoolValue.hpp"
#include "Type.hpp"

BoolValue::BoolValue(bool value)
    : PrimitiveValue(Type::BOOL,value)
{
    
}

void BoolValue::linkWithClass() {
    
}

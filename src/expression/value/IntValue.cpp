#include "IntValue.hpp"
#include "Type.hpp"

IntValue::IntValue(int value)
    : PrimitiveValue(Type::INT,value)
{
    
}

void IntValue::linkWithClass() {
    
}

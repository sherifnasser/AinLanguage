#include "DoubleValue.hpp"
#include "Type.hpp"

DoubleValue::DoubleValue(long double value)
    : PrimitiveValue(Type::DOUBLE,value)
{
    
}

void DoubleValue::linkWithClass() {
    
}

#include "LongValue.hpp"
#include "Type.hpp"

LongValue::LongValue(long long value)
:PrimitiveValue(Type::LONG,value){}
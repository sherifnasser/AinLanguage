#include "ULongValue.hpp"
#include "Type.hpp"

ULongValue::ULongValue(unsigned long long value)
:PrimitiveValue(Type::ULONG,value){}

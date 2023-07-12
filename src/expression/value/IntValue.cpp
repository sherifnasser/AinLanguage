#include "IntValue.hpp"
#include "IntClassScope.hpp"
#include "Type.hpp"
#include <memory>

IntValue::IntValue(int value)
:PrimitiveValue(Type::INT,value){}
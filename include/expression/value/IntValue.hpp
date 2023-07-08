#pragma once
#include "PrimitiveValue.hpp"
class IntValue:public PrimitiveValue<int>{
    public:
        IntValue(int value);
        void linkWithClass()override;
};
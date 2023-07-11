#pragma once
#include "PrimitiveValue.hpp"
class DoubleValue:public PrimitiveValue<long double>{
    public:
        DoubleValue(long double value);
        void linkWithClass()override;
        void unlinkWithClass()override;
};
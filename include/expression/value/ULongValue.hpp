#pragma once
#include "PrimitiveValue.hpp"
class ULongValue:public PrimitiveValue<unsigned long long>{
    public:
        ULongValue(unsigned long long value);
        void linkWithClass()override;
        void unlinkWithClass()override;
};
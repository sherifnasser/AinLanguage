#pragma once
#include "PrimitiveValue.hpp"
class UIntValue:public PrimitiveValue<unsigned int>{
    public:
        UIntValue(unsigned int value);
        void linkWithClass()override;
        void unlinkWithClass()override;
};
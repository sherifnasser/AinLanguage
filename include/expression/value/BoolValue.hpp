#pragma once
#include "PrimitiveValue.hpp"
class BoolValue:public PrimitiveValue<bool>{
    public:
        BoolValue(bool value);
        void linkWithClass()override;
};
#pragma once
#include "PrimitiveValue.hpp"
class CharValue:public PrimitiveValue<wchar_t>{
    public:
        CharValue(wchar_t value);
        void linkWithClass()override;
};
#pragma once
#include "IValue.hpp"
#include "Type.hpp"
class UnitValue:public IValue{
    public:
        UnitValue();

        void linkWithClass() override;
        
        std::wstring toString() override;
};
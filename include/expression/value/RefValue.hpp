#pragma once
#include "IValue.hpp"
class RefValue:public IValue{
    public:
        void linkWithClass() override;
        void unlinkWithClass() override;
        std::wstring toString() override;
        RefValue();
};
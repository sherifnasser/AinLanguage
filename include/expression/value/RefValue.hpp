#pragma once
#include "IValue.hpp"
class RefValue:public IValue{
    private:
        int address;
    public:
        void linkWithClass() override;
        void unlinkWithClass() override;
        std::wstring toString() override;
        RefValue(int value=0);
        int getAddress()const;
};
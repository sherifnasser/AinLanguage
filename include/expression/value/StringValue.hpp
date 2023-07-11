#pragma once
#include "IValue.hpp"
#include <string>

class StringValue:public IValue{
    private:
        std::wstring value;
    public:
        StringValue(std::wstring value);
        void linkWithClass()override;
        void unlinkWithClass()override;
        std::wstring toString()override;
};
#pragma once
#include "IValue.hpp"
#include <string>

class StringValue:public IValue{
    private:
        std::wstring value;
    StringValue(std::wstring value);
};
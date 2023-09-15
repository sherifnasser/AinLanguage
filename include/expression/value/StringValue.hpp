#pragma once
#include "IValue.hpp"
#include "StringClassScope.hpp"
#include <string>

class StringValue:public IValue{
    private:
        std::wstring value;
        std::shared_ptr<StringClassScope> classScope;
    public:
        StringValue(std::wstring value);
        void linkWithClass()override;
        void unlinkWithClass()override;
        std::wstring toString()override;
        std::wstring getValue() const;
};
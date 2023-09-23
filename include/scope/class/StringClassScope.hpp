#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
#include <string>
class StringClassScope:public ClassScope{
    private:
        SharedVector<std::wstring> valueStack;
    public:
        StringClassScope();
        std::wstring getValue();
        void setValue(std::wstring value);
        void pushNewValue();
        void popLastValue();
};
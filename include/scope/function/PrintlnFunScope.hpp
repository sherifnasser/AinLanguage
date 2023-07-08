#pragma once
#include "BuiltInFunScope.hpp"
class PrintlnFunScope:public BuiltInFunScope{
    public:
        PrintlnFunScope();
        void check() override;
        SharedIValue invoke(std::map<std::wstring, SharedIValue> params) override;
};
#pragma once
#include"IExpression.hpp"

class BoolExpression:public IExpression{
    private:
        std::wstring val;
    public:
        BoolExpression(std::wstring &val);
        std::wstring evaluate(SharedScope evalScope) override;
        void print(std::wstring tabsize=L"") override;
        static bool boolFromStr(std::wstring s);
        static std::wstring strFromBool(bool b);
};
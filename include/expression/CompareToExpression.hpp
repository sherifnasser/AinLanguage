#pragma once
#include "BoolValue.hpp"
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <functional>
#include <memory>
class CompareToExpression:public IExpression{
    private:
        SharedIExpression compareToFunEx;
    protected:
        int evaluateCompareToFun();
    public:
        CompareToExpression(int lineNumber,SharedIExpression compareToFunEx);
        std::vector<std::wstring> prettyPrint()override;
        void check(SharedBaseScope checkScope)override;
        class Less;
        class LessEqual;
        class Greater;
        class GreaterEqual;
};

class CompareToExpression::Less:public CompareToExpression{
    public:
        using CompareToExpression::CompareToExpression;
        SharedIValue evaluate()override;
};

class CompareToExpression::LessEqual:public CompareToExpression{
    public:
        using CompareToExpression::CompareToExpression;
        SharedIValue evaluate()override;
};

class CompareToExpression::Greater:public CompareToExpression{
    public:
        using CompareToExpression::CompareToExpression;
        SharedIValue evaluate()override;
};

class CompareToExpression::GreaterEqual:public CompareToExpression{
    public:
        using CompareToExpression::CompareToExpression;
        SharedIValue evaluate()override;
};
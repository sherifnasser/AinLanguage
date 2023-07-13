#pragma once
#include "BoolValue.hpp"
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <functional>
#include <memory>
class EqualityExpression:public IExpression{
    private:
        SharedIExpression equalsFunEx;
    protected:
        bool evaluateEqualsFun();
    public:
        EqualityExpression(int lineNumber,SharedIExpression equalsFunEx);
        std::vector<std::wstring> prettyPrint()override;
        void check(SharedBaseScope checkScope)override;

        class EqualEqual;
        
        class NotEqual;
};

class EqualityExpression::EqualEqual:public EqualityExpression{
    public:
        using EqualityExpression::EqualityExpression;
        SharedIValue evaluate()override;
};

class EqualityExpression::NotEqual:public EqualityExpression{
    public:
        using EqualityExpression::EqualityExpression;
        SharedIValue evaluate()override;
};
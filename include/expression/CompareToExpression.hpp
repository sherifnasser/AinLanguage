#pragma once
#include "BoolValue.hpp"
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <functional>
#include <memory>
class CompareToExpression:public IExpression{
    private:
        std::function<std::shared_ptr<BoolValue>(int)> evaluationFun;
        SharedIExpression compareToFunEx;
    public:
        enum class EVALUATION_FUN{
            GREATER,GREATER_EQUAL,LESS,LESS_EQUAL
        };
        CompareToExpression(int lineNumber,SharedIExpression compareToFunEx,EVALUATION_FUN evaluationFun);
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;
};
#pragma once
#include "BoolValue.hpp"
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <functional>
#include <memory>

class LogicalExpression:public IExpression{
    private:
        SharedIExpression left;
        SharedIExpression right;
        bool evaluateLeft();
    protected:
        std::shared_ptr<BoolValue> evaluateRight();
    public:
        LogicalExpression(
            int lineNumber,
            SharedIExpression left,
            SharedIExpression right
        );
        void check(SharedBaseScope checkScope)override;

        std::vector<std::wstring> prettyPrint()override;

        class Or;

        class And;
};

class LogicalExpression::Or:public LogicalExpression{
    public:
        using LogicalExpression::LogicalExpression;
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
};

class LogicalExpression::And:public LogicalExpression{
    public:
        using LogicalExpression::LogicalExpression;
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
};
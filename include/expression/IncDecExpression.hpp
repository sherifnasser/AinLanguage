#pragma once
#include "AssignStatement.hpp"
#include "OperatorFunInvokeExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
#include <utility>
class IncDecExpression:public OperatorFunInvokeExpression{
    private:
        std::shared_ptr<AssignStatement::AssignExpression> ex;
    protected:
        /**
        Returns a pair of {newVal, oldVal} respectively
        */
        std::pair<SharedIValue, SharedIValue> evaluateNewAndOldValues();

        void check(SharedBaseScope checkScope) override;
    public:
        IncDecExpression(
            int lineNumber,
            std::wstring opName,
            std::shared_ptr<AssignStatement::AssignExpression> ex
        );
        void accept(ASTVisitor *visitor) override;
        class PreIncDecExpression;
        class PostIncDecExpression;
};

class IncDecExpression::PreIncDecExpression:public IncDecExpression{
    public:
        using IncDecExpression::IncDecExpression;
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
};

class IncDecExpression::PostIncDecExpression:public IncDecExpression{
    public:
        using IncDecExpression::IncDecExpression;
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;

};
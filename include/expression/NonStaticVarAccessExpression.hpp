#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class NonStaticVarAccessExpression:public IExpression{
    private:
        std::wstring varName;
        SharedIExpression inside;
        void checkType();
    public:
        NonStaticVarAccessExpression(
            int lineNumber,
            std::wstring varName,
            SharedIExpression inside
        );
        void accept(ASTVisitor *visitor) override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;

        std::wstring getVarName() const;

        SharedIExpression getInside() const;
};
#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class NonStaticVarAccessExpression:public IExpression{
    private:
        std::wstring varName;
        SharedIExpression inside;
    public:
        NonStaticVarAccessExpression(
            int lineNumber,
            std::wstring varName,
            SharedIExpression inside
        );
        void accept(ASTVisitor *visitor) override;

        std::wstring getVarName() const;

        SharedIExpression getInside() const;
};
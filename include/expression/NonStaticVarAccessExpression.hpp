#pragma once
#include "AssignStatement.hpp"
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>
class NonStaticVarAccessExpression:public AssignStatement::AssignExpression{
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
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;
        void assign(SharedIValue newVal)override;
};
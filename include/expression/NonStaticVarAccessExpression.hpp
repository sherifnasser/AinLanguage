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
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;
};
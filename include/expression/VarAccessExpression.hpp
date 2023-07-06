#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>

class VarAccessExpression:public IExpression{
    private:
        std::wstring varName;
        SharedVariable var;
    public:
        VarAccessExpression(int lineNumber,std::wstring varName,SharedVariable var);
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;

};
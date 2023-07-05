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
        void check(SharedBaseScope checkScope)override;

};
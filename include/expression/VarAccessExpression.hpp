#pragma once
#include "AssignStatement.hpp"
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>

class VarAccessExpression:public AssignStatement::AssignExpression{
    private:
        std::wstring varName;
        SharedVariable var;
        void setVar(SharedVariable var);
    public:
        VarAccessExpression(int lineNumber,std::wstring varName,SharedVariable var);
        std::vector<std::wstring> prettyPrint()override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;
        void assign(SharedIValue newVal)override;
};
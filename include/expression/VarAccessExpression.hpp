#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
#include <string>

class VarAccessExpression:public IExpression{
    private:
        std::wstring varName;
        SharedVariable var;
        void setVar(SharedVariable var);
        void checkType();
    public:
        VarAccessExpression(int lineNumber,std::wstring varName,SharedVariable var);
        void accept(ASTVisitor *visitor) override;
        SharedIValue evaluate()override;
        void check(SharedBaseScope checkScope)override;

        SharedVariable getVar() const;
        std::wstring getVarName() const;
};
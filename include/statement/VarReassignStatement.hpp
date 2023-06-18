#pragma once
#include "IStatement.hpp"

class VarReassignStatement:public IStatement
{
    private:
        std::wstring varname;
        SharedIExpression ex;
    public:
        VarReassignStatement(SharedScope runScope,std::wstring varname,SharedIExpression ex);
        void run() override;
};
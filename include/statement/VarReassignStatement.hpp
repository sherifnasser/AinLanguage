#pragma once
#include "IOldStatement.hpp"

class VarReassignStatement:public IOldStatement
{
    private:
        std::wstring varname;
        SharedIOldExpression ex;
    public:
        VarReassignStatement(SharedScope runScope,std::wstring varname,SharedIOldExpression ex);
        void run() override;
};
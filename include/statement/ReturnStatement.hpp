#pragma once
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"

class ReturnStatement:public IStatement
{
    private:
        SharedIExpression ex;
    public:
        ReturnStatement(
            int lineNumber,
            SharedFunScope funScope,
            SharedIExpression ex
        );
        void check() override;
        void run() override;
};
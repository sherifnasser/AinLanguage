#pragma once
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"
class BreakStatement:public IStatement{
    private:
        SharedLoopScope loopScope;
    public:

        BreakStatement(
            int lineNumber,
            SharedBaseScope runScope,
            SharedLoopScope loopScope
        );

        void check() override;
        
        void run() override;
};
#pragma once
#include "IStatement.hpp"
class ContinueStatement:public IStatement{
    private:
        SharedLoopScope loopScope;
    public:
    
        ContinueStatement(
            int lineNumber,
            SharedBaseScope runScope,
            SharedLoopScope loopScope
        );

        void check() override;
        
        void run() override;

};
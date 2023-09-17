#pragma once
#include "StmListScope.hpp"
class LoopScope:public StmListScope{
    private:
        bool toBreak;
        bool toContinue;
        SharedFunScope containingFunScope;
    public:
        LoopScope(SharedBaseScope parentScope);
        void runStmList();
        void check() override;
        bool isBreak();
        bool isContinue();
        bool isReturn();
        void makeBreak();
        void makeContinue();
        void resetBreak();
        void resetContinue();
};
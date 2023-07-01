#pragma once
#include"Scope.hpp"

class OldFunScope:public Scope
{
    private:
        std::wstring returnType;
        std::wstring returnValue;
        SharedVector<std::pair<std::wstring,std::wstring>> args;
        SharedVector<SharedIOldStatement> stmList;
    public:
        OldFunScope(
            SharedScope parentScope,
            std::wstring &name,
            std::wstring &returnType,
            SharedVector<std::pair<std::wstring,std::wstring>> args
        );
        SharedVector<std::pair<std::wstring,std::wstring>> getArgs();
        std::wstring getReturnType();
        std::wstring getReturnValue();
        SharedVector<SharedIOldStatement> getStmList();
        void setStmList(SharedVector<SharedIOldStatement> stmList);
        void setReturnValue(std::wstring returnValue);
        void call();
        
};
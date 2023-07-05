#pragma once
#include "SharedPtrTypes.hpp"
#include <string>
class IExpression{
    protected:
        int lineNumber;
        SharedType returnType;
    public:
        IExpression(int lineNumber,SharedType returnType);
        virtual void print(std::wstring tabSize=L"")=0;
        virtual SharedIValue evaluate()=0;
        virtual void check(SharedBaseScope checkScope)=0;
        SharedType getReturnType();
};
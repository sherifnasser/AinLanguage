#pragma once
#include "SharedPtrTypes.hpp"
#include <string>
class IExpression{
    protected:
        SharedClassScope returnType;
    public:
        virtual void print(std::wstring tabSize=L"")=0;
        virtual SharedIValue evaluate()=0;
        virtual void check()=0;
};
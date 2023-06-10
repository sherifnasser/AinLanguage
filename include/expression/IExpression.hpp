#pragma once
#include "SharedPtrTypes.hpp"

class Scope;
class Variable;
class Constant;
class FunScope;
class ClassScope;

class IExpression{
    public:
        virtual std::wstring evaluate(SharedScope evalScope)=0;
        virtual void print(std::wstring tabSize=L"")=0;
};
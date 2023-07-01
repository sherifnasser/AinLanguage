#pragma once
#include "SharedPtrTypes.hpp"

class Scope;
class OldVariable;
class OldConstant;
class OldFunScope;
class ClassScope;

class IOldExpression{
    public:
        virtual std::wstring evaluate(SharedScope evalScope)=0;
        virtual void print(std::wstring tabSize=L"")=0;
};
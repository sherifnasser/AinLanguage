#pragma once
#include "SharedPtrTypes.hpp"
class Variable{
    private:
        SharedVarDecl decl;
        SharedIValue value;
    public:
        Variable(SharedWString name,SharedType type,SharedBool isVal);
        Variable(SharedVarDecl decl);

        SharedIValue getValue();

        void setValue(SharedIValue value);

        SharedWString getName();

        SharedBool isValue();

        SharedType getType();
};
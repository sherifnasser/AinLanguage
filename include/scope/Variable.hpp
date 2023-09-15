#pragma once
#include "SharedPtrTypes.hpp"
class Variable{
    private:
        SharedVarDecl decl;
        SharedVector<SharedIValue> values;
    public:
        Variable(SharedWString name,SharedType type,SharedBool isVal);
        Variable(SharedVarDecl decl);

        SharedIValue getValue();

        void setValue(SharedIValue value);

        SharedWString getName();

        SharedBool isValue();

        bool hasImplicitType();

        void pushNewValue();

        void popLastValue();

        SharedType getType();

        void setType(SharedType type);

};
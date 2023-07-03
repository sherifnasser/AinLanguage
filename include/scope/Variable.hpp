#pragma once
#include "SharedPtrTypes.hpp"
class Variable{
    private:
        SharedWString name;
        SharedType type;
        SharedBool isVal;
        SharedIValue value;
    public:
        Variable(SharedWString name,SharedType type,SharedBool isVal);

        SharedIValue getValue();

        void setValue(SharedIValue value);

        SharedWString getName();

        SharedBool isValue();
};
#pragma once
#include "SharedPtrTypes.hpp"
class Variable{
    private:
        SharedWString name;
        SharedBool isVal;
        SharedClassScope type;
        SharedIValue value;
    public:
        Variable(SharedWString name,SharedBool isVal);

        SharedIValue getValue();

        void setValue(SharedIValue value);

        SharedClassScope getType();
        
        void setType(SharedClassScope type);

        SharedWString getName();

        SharedBool isValue();
};
#pragma once
#include "SharedPtrTypes.hpp"
class IValue{
    protected:
        SharedClassScope type;
        IValue(SharedClassScope type);
    public:
        SharedClassScope getType();
        virtual ~IValue();
};
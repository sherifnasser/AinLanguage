#pragma once
#include "SharedPtrTypes.hpp"
class IValue{
    protected:
        SharedType type;
        IValue(SharedType type);
    public:
        SharedType getType();
        virtual ~IValue();
};
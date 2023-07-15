#pragma once
#include "IValue.hpp"
#include "SharedPtrTypes.hpp"
class ObjectValue:public IValue{
    public:
        ObjectValue();
        ObjectValue(SharedType type);
        void linkWithClass()override;
        void unlinkWithClass()override;
        std::wstring toString()override;
};
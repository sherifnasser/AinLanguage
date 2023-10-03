#pragma once
#include "PrimitiveValue.hpp"
#include <memory>
#include <vector>
class ArrayValue:public PrimitiveValue<std::vector<SharedIValue>>{
    public:
        /**
        NOTE: The @param type should be of type Type::Array. Be careful as we want to avoid casting.
        */
        ArrayValue(SharedType type,int capacity);
        std::wstring toString() override;
        int size()const;
};
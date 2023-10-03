#pragma once
#include "PrimitiveClassScope.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
class ArrayClassScope:public PrimitiveClassScope<std::vector<SharedIValue>>{
    public:
        ArrayClassScope():
        PrimitiveClassScope<std::vector<SharedIValue>>(Type::ARRAY_NAME){}
};
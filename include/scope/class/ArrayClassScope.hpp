#pragma once
#include "PrimitiveClassScope.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "Variable.hpp"
#include <memory>
#include <string>
class ArrayClassScope:public PrimitiveClassScope<std::vector<SharedIValue>>{
    public:
        static inline auto CAPACITY_NAME=std::make_shared<std::wstring>(L"السعة");

        ArrayClassScope():
        PrimitiveClassScope<std::vector<SharedIValue>>(Type::ARRAY_NAME){    
            (*getPublicVariables())[*CAPACITY_NAME]=
                std::make_shared<Variable>(
                    CAPACITY_NAME,
                    Type::INT,
                    std::make_shared<bool>(true)
                );
        }
};
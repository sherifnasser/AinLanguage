#pragma once
#include "IntClassScope.hpp"
#include "PrimitiveValue.hpp"
#include <memory>
class IntValue:public PrimitiveValue<int>{
    private:
        std::shared_ptr<IntClassScope> intClassScope;
    public:
        IntValue(int value);
        void linkWithClass()override;
        void unlinkWithClass()override;
};
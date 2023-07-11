#include "IntValue.hpp"
#include "IntClassScope.hpp"
#include "Type.hpp"
#include <memory>

IntValue::IntValue(int value)
    : PrimitiveValue(Type::INT,value)
{

}

void IntValue::linkWithClass(){
    if(!intClassScope)
        intClassScope=
            std::dynamic_pointer_cast<IntClassScope>(Type::INT->getClassScope())
        ;

    intClassScope->pushNewValue();
    intClassScope->setValue(value);
}

void IntValue::unlinkWithClass(){
    intClassScope->popLastValue();
}

#include "StringValue.hpp"
#include "StringClassScope.hpp"
#include "Type.hpp"

StringValue::StringValue(std::wstring value)
:IValue(Type::STRING),value(value){}

void StringValue::linkWithClass() {
    if(!classScope)
        classScope=
            std::dynamic_pointer_cast<StringClassScope>(type->getClassScope())
        ;

    classScope->pushNewValue();
    classScope->setValue(value);
}

void StringValue::unlinkWithClass(){
    classScope->popLastValue();
}

std::wstring StringValue::toString(){
    return this->value;
}

std::wstring StringValue::getValue()const{
    return this->value;
}

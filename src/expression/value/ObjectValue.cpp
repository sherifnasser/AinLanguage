#include "ObjectValue.hpp"
#include "Type.hpp"
#include <memory>

ObjectValue::ObjectValue(SharedType type)
:IValue(type)
{}

void ObjectValue::linkWithClass(){
    
}

void ObjectValue::unlinkWithClass(){
    
}

std::wstring ObjectValue::toString(){
    return *type->getName();
}

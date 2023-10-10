#include "RefValue.hpp"
#include "Type.hpp"

void RefValue::linkWithClass() {
    // TODO
}

void RefValue::unlinkWithClass() {
    // TODO
}

std::wstring RefValue::toString() {
    return L"";
}

RefValue::RefValue(int value)
    : IValue(Type::INT),
    address(value){}
    
int RefValue::getAddress()const{
    return address;
}
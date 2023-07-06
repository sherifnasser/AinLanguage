#pragma once
#include "IValue.hpp"
#include <string>
template<typename T>
class PrimitiveValue:public IValue{
    protected:
        T value;
    public:
        PrimitiveValue<T>(SharedType type,T value);
        T getValue();
        std::wstring toString()override;
};


template<typename T>
PrimitiveValue<T>::PrimitiveValue(SharedType type,T value)
:IValue(type),value(value){}

template<typename T>
T PrimitiveValue<T>::getValue(){
    return this->value;
}

template<typename T>
std::wstring PrimitiveValue<T>::toString(){
    return std::to_wstring(value);
}
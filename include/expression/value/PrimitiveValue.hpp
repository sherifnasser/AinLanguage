#pragma once
#include "IValue.hpp"
template<typename T>
class PrimitiveValue:public IValue{
    protected:
        T value;
    public:
        PrimitiveValue<T>(SharedClassScope type,T value);
        T getValue();
};


template<typename T>
PrimitiveValue<T>::PrimitiveValue(SharedClassScope type,T value)
:IValue(type),value(value){}

template<typename T>
T PrimitiveValue<T>::getValue(){
    return this->value;
}
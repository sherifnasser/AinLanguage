#pragma once
#include "IValue.hpp"
#include "PrimitiveClassScope.hpp"
#include "Type.hpp"
#include <memory>
#include <string>
template<typename T>
class PrimitiveValue:public IValue{
    protected:
        T value;
        std::shared_ptr<PrimitiveClassScope<T>> classScope;
    public:
        PrimitiveValue<T>(SharedType type,T value);
        T getValue();
        std::wstring toString()override;
        void linkWithClass()override;
        void unlinkWithClass()override;
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

template<typename T>
inline void PrimitiveValue<T>::linkWithClass(){
    if(!classScope)
        classScope=
            std::dynamic_pointer_cast<PrimitiveClassScope<T>>(type->getClassScope())
        ;

    classScope->pushNewValue();
    classScope->setValue(value);
}

template<typename T>
inline void PrimitiveValue<T>::unlinkWithClass() {
    classScope->popLastValue();
}

#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
template<typename T>
class PrimitiveClassScope:public ClassScope{
    private:
        SharedVector<T> valueStack;
    public:
        PrimitiveClassScope(SharedWString name);
        T getValue();
        void setValue(T value);
        void pushNewValue();
        void popLastValue();
};

template<typename T>
PrimitiveClassScope<T>::PrimitiveClassScope(SharedWString name)
:ClassScope(*name,PackageScope::AIN_PACKAGE),
valueStack(std::make_shared<std::vector<T>>())
{}

template<typename T>
T PrimitiveClassScope<T>::getValue(){
    return (*valueStack)[valueStack->size()-1];
}

template<typename T>
void PrimitiveClassScope<T>::setValue(T value){
    (*valueStack)[valueStack->size()-1]=value;
}

template<typename T>
void PrimitiveClassScope<T>::pushNewValue(){
    valueStack->push_back(0);
}

template<typename T>
void PrimitiveClassScope<T>::popLastValue(){
    valueStack->pop_back();
}
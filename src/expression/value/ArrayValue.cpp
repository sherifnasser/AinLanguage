#include "ArrayValue.hpp"
#include "PrimitiveValue.hpp"
#include "SharedPtrTypes.hpp"
#include <vector>

ArrayValue::ArrayValue(SharedType type,int capacity)
:PrimitiveValue(type,std::vector<SharedIValue>{}){
    for(int i=0;i<capacity;i++){
        value.push_back(nullptr);
    }
}

std::wstring ArrayValue::toString(){
    return L"["+type->asArray()->getType()->getClassScope()->getName()+L"]";
}

int ArrayValue::size()const{
    return value.size();
}
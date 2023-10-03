#include "ArrayValue.hpp"
#include "IntValue.hpp"
#include "ObjectValue.hpp"
#include "PrimitiveValue.hpp"
#include "SharedPtrTypes.hpp"
#include "ArrayClassScope.hpp"
#include "Type.hpp"
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

ArrayValue::ArrayValue(SharedType type,int capacity)
:
    IValue(type),
    PrimitiveValue(type,std::vector<SharedIValue>{}),
    ObjectValue(
        type,
        std::make_shared<std::unordered_map<std::wstring,SharedIValue>>(
            std::unordered_map<std::wstring,SharedIValue>{
                {
                    *ArrayClassScope::CAPACITY_NAME,
                    std::make_shared<IntValue>(capacity)  
                }
            }
        )    
    )
{
    for(int i=0;i<capacity;i++){
        value.push_back(nullptr);
    }
}

std::wstring ArrayValue::toString(){
    return L"["+type->asArray()->getType()->getClassScope()->getName()+L"]";
}

void ArrayValue::linkWithClass(){
    PrimitiveValue<std::vector<SharedIValue>>::linkWithClass();
    ObjectValue::linkWithClass();
}

void ArrayValue::unlinkWithClass(){
    value=Type::ARRAY_CLASS->getValue();
    PrimitiveValue<std::vector<SharedIValue>>::unlinkWithClass();
    ObjectValue::unlinkWithClass();
}

int ArrayValue::size()const{
    return value.size();
}
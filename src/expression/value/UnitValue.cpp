#include "UnitValue.hpp"

UnitValue::UnitValue():IValue(Type::UNIT){}

void UnitValue::linkWithClass(){}

void UnitValue::unlinkWithClass() {
    
}

std::wstring UnitValue::toString(){return *Type::UNIT->getName();}

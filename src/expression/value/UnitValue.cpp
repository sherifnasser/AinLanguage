#include "UnitValue.hpp"

UnitValue::UnitValue():IValue(Type::UNIT){}

void UnitValue::linkWithClass(){}

std::wstring UnitValue::toString(){return *Type::UNIT->getName();}

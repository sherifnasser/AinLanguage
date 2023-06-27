#include"OldConstant.hpp"

OldConstant::OldConstant(SharedScope parentScope, std::wstring &name, std::wstring &type):
OldVariable(parentScope,name,type){}

void OldConstant::setCurrentValue(std::wstring value){
    if(isInitialized)
        std::__throw_runtime_error("Cannot reassign a OldConstant value.");
    else
        OldVariable::setCurrentValue(value);
}
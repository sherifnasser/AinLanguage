#include"Constant.hpp"

Constant::Constant(SharedScope parentScope, std::wstring &name, std::wstring &type):
Variable(parentScope,name,type){}

void Constant::setCurrentValue(std::wstring value){
    if(isInitialized)
        std::__throw_runtime_error("Cannot reassign a constant value.");
    else
        Variable::setCurrentValue(value);
}
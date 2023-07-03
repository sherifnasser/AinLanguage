#include "Variable.hpp"
#include "SharedPtrTypes.hpp"
#include "VarDecl.hpp"



Variable::Variable(SharedWString name,SharedType type,SharedBool isVal)
:name(name),type(type),isVal(isVal){}

SharedIValue Variable::getValue(){
    return value;
}

void Variable::setValue(SharedIValue value){
    this->value=value;
}

SharedWString Variable::getName(){
    return this->name;
}

SharedBool Variable::isValue(){
    return isVal;
}

SharedType Variable::getType(){
    return this->type;
}
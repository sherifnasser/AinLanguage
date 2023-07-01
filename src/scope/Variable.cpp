#include "Variable.hpp"
#include "SharedPtrTypes.hpp"
#include "VarDecl.hpp"

Variable::Variable(SharedWString name,SharedBool isVal)
:name(name),isVal(isVal){}

SharedIValue Variable::getValue(){
    return value;
}

void Variable::setValue(SharedIValue value){
    this->value=value;
}

SharedClassScope Variable::getType(){
    return this->type;
}

void Variable::setType(SharedClassScope type){
    this->type=type;
}

SharedWString Variable::getName(){
    return this->name;
}

SharedBool Variable::isValue(){
    return isVal;
}
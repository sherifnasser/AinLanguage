#include "Variable.hpp"
#include "SharedPtrTypes.hpp"
#include "VarDecl.hpp"
#include <memory>

Variable::Variable(SharedWString name,SharedType type,SharedBool isVal){
    this->decl=std::make_shared<VarDecl>(name,type,isVal);
}

Variable::Variable(SharedVarDecl decl):decl(decl){}

SharedIValue Variable::getValue(){
    return value;
}

void Variable::setValue(SharedIValue value){
    this->value=value;
}

SharedWString Variable::getName(){
    return this->decl->name;
}

SharedBool Variable::isValue(){
    return this->decl->isVal;
}

SharedType Variable::getType(){
    return this->decl->type;
}
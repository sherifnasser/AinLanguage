#include "Variable.hpp"
#include "SharedPtrTypes.hpp"
#include "VarDecl.hpp"
#include <memory>
#include <vector>

Variable::Variable(
    SharedWString name,
    SharedType type,
    SharedBool isVal
):
decl(std::make_shared<VarDecl>(name,type,isVal)),
values(std::make_shared<std::vector<SharedIValue>>())
{}

Variable::Variable(SharedVarDecl decl):
decl(decl),
values(std::make_shared<std::vector<SharedIValue>>())
{}

SharedIValue Variable::getValue(){
    return values->at(values->size()-1);
}

void Variable::setValue(SharedIValue value){
    this->values->at(values->size()-1)=value;
}

SharedWString Variable::getName(){
    return this->decl->name;
}

SharedBool Variable::isValue(){
    return this->decl->isVal;
}

bool Variable::hasImplicitType(){
    return this->decl->hasImplicitType();
}

void Variable::pushNewValue(){
    this->values->push_back(nullptr);
}

void Variable::popLastValue(){
    this->values->pop_back();
}

SharedType Variable::getType(){
    return this->decl->type;
}

void Variable::setType(SharedType type){
    this->decl->type=type;
}
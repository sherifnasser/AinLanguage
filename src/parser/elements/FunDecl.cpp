#include "FunDecl.hpp"
#include "FunParam.hpp"
#include "Type.hpp"

FunDecl::FunDecl(
    SharedWString name,
    SharedType returnType,
    SharedBool isOperator,
    SharedVector<SharedFunParam> params
):name(name),returnType(returnType),isOperator(isOperator),params(params){}

bool FunDecl::operator==(const FunDecl& declaration)const{

    if(params->size()!=declaration.params->size())
        return false;

    for(int i=0;i<params->size();i++){
        if(*params->at(i)!=*(declaration.params->at(i)))
            return false;
    }
    
    if(!(returnType&&declaration.returnType))
        return false;

    return
        *name==*declaration.name
        &&
        *returnType==*declaration.returnType
    ;
}

bool FunDecl::operator!=(const FunDecl& declaration)const{
    return !(*this==declaration);
}

bool FunDecl::hasImplicitReturnType()const {
    return this->returnType==nullptr;
}

    

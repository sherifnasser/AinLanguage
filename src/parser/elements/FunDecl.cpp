#include "FunDecl.hpp"
#include "FunParamater.hpp"
#include "Type.hpp"

FunDecl::FunDecl(
    SharedWString name,
    SharedType returnType,
    SharedVector<SharedFunParamater> params
):name(name),returnType(returnType),params(params){}

bool FunDecl::operator==(FunDecl& declaration){

    if(params->size()!=declaration.params->size())
        return false;

    for(int i=0;i<params->size();i++){
        if(*params->at(i)!=*(declaration.params->at(i)))
            return false;
    }
    
    return
        *name==*declaration.name
        &&
        *returnType==*declaration.returnType
    ;
}

bool FunDecl::operator!=(FunDecl& declaration) {
    return !(*this==declaration);
}

    

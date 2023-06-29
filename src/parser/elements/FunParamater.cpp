#include "FunParamater.hpp"
#include "SharedPtrTypes.hpp"

FunParamater::FunParamater(SharedWString name, SharedType type)
:name(name),type(type){}

bool FunParamater::operator==(const FunParamater& param)const{
    return 
        *this->name==*param.name
        &&
        this->type==param.type
    ;
}

bool FunParamater::operator!=(const FunParamater& param)const{
    return !(*this==param);
}

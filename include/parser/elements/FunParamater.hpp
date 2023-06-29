#pragma once
#include "SharedPtrTypes.hpp"
struct FunParamater{
    SharedWString name;
    SharedType type;

    FunParamater(SharedWString name, SharedType type);

    bool operator==(const FunParamater& param)const;
    bool operator!=(const FunParamater& param)const;
};
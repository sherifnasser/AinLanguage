#pragma once
#include "SharedPtrTypes.hpp"
struct FunParamater{
    SharedWString name;
    SharedType type;

    FunParamater(SharedWString name, SharedType type);

    bool operator==(FunParamater& param);
    bool operator!=(FunParamater& param);
};
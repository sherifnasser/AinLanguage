#pragma once
#include "SharedPtrTypes.hpp"
struct FunDecl{
    SharedWString name;
    SharedType returnType;
    SharedVector<SharedFunParamater> params;
    FunDecl(
        SharedWString name,
        SharedType returnType,
        SharedVector<SharedFunParamater> params
    );

    bool operator==(FunDecl& declaration);
    bool operator!=(FunDecl& declaration);
};
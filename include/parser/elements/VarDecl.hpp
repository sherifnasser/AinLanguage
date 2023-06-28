#pragma once
#include "SharedPtrTypes.hpp"
struct VarDecl{
    SharedWString name;
    SharedType type;
    SharedBool isVal;

    VarDecl(
        SharedWString name,
        SharedType type,
        SharedBool isVal
    );

    bool operator==(VarDecl& declaration);
    bool operator!=(VarDecl& declaration);
};
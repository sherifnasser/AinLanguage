#pragma once
#include "SharedPtrTypes.hpp"
#include <string>
struct Type{
    SharedWString name;
    Type(SharedWString name);
    bool operator==(const Type& type)const;
    bool operator!=(const Type& type)const;
    static SharedType UNIT;
    static SharedType INT;
    static SharedType LONG;
    static SharedType FLOAT;
    static SharedType UINT;
    static SharedType ULONG;
    static SharedType DOUBLE;
    static SharedType BOOL;
};
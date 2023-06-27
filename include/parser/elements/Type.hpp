#pragma once
#include "SharedPtrTypes.hpp"
#include <string>
struct Type{
    SharedWString name;
    Type(SharedWString name);
    bool operator==(Type& type);
    bool operator!=(Type& type);
    static SharedType UNIT;
};
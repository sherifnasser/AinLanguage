#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class ULongClassScope:public ClassScope{
    public:
        ULongClassScope():ClassScope(*Type::ULONG_NAME,PackageScope::AIN_PACKAGE){}
};
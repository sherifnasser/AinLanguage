#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class UIntClassScope:public ClassScope{
    public:
        UIntClassScope():ClassScope(*Type::UINT_NAME,PackageScope::AIN_PACKAGE){}
};
#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class UnitClassScope:public ClassScope{
    public:
        UnitClassScope():ClassScope(*Type::UNIT_NAME,PackageScope::AIN_PACKAGE){}
};
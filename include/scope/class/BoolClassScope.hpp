#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class BoolClassScope:public ClassScope{
    public:
        BoolClassScope():ClassScope(*Type::BOOL_NAME,PackageScope::AIN_PACKAGE){}
};
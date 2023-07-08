#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class StringClassScope:public ClassScope{
    public:
        StringClassScope():ClassScope(*Type::STRING_NAME,PackageScope::AIN_PACKAGE){}
};
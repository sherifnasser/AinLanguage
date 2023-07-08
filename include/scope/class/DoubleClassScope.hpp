#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class DoubleClassScope:public ClassScope{
    public:
        DoubleClassScope():ClassScope(*Type::DOUBLE_NAME,PackageScope::AIN_PACKAGE){}
};
#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class FloatClassScope:public ClassScope{
    public:
        FloatClassScope():ClassScope(*Type::FLOAT_NAME,PackageScope::AIN_PACKAGE){}
};
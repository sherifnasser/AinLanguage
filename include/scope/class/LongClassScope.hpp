#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class LongClassScope:public ClassScope{
    public:
        LongClassScope():ClassScope(*Type::LONG_NAME,PackageScope::AIN_PACKAGE){}
};
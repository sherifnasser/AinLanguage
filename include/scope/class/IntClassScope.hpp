#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class IntClassScope:public ClassScope{
    public:
        IntClassScope():ClassScope(*Type::INT_NAME,PackageScope::AIN_PACKAGE){}
};
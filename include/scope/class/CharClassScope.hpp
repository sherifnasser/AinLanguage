#pragma once
#include "ClassScope.hpp"
#include "PackageScope.hpp"
#include "Type.hpp"
class CharClassScope:public ClassScope{
    public:
        CharClassScope():ClassScope(*Type::CHAR_NAME,PackageScope::AIN_PACKAGE){}
};
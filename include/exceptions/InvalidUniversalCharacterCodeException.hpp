#pragma once
#include <iostream>
#include "AinException.hpp"

class InvalidUniversalCharacterCodeException:public AinException{

    public:
    InvalidUniversalCharacterCodeException(int lineNumber,std::wstring literal)
    :AinException(
        AinException::errorWString(
            L"في السطر "+std::to_wstring(lineNumber)+
            L" عند "+literal+
            L"\n"+L"رمز اليونيكود غير صالح."
        )
    ){}
};
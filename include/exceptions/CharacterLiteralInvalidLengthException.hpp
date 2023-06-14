#pragma once
#include <iostream>
#include "AinException.hpp"

class CharacterLiteralInvalidLengthException:public AinException{

    public:
    CharacterLiteralInvalidLengthException(int lineNumber,std::wstring literal)
    :AinException(
        AinException::errorWString(
            L"في السطر "+std::to_wstring(lineNumber)+
            L" عند "+literal+
            L"\n"+L"يجب أن يحتوى على حرفٍ واحدٍ فقط."
        )
    ){}
};
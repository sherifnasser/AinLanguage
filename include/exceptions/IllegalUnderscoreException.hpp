#pragma once
#include <iostream>
#include "AinException.hpp"

class IllegalUnderscoreException:public AinException{

    public:
    IllegalUnderscoreException(int lineNumber,std::wstring token)
    :AinException(
        AinException::errorWString(
            L"في السطر "+std::to_wstring(lineNumber)+
            L"\n"+
            token+
            L" يوجد شَرطَة سُفلية غير صالحة"
        )
    ){}
};
#pragma once
#include <iostream>
#include "AinException.hpp"

class UnsupportedTokenException:public AinException{

    public:
    UnsupportedTokenException(int lineNumber,std::wstring token)
    :AinException(
        AinException::errorWString(
            L"في السطر "+std::to_wstring(lineNumber)+
            L"\n"+
            token+
            L" قيمة غير مدعومة."
        )
    ){}
};
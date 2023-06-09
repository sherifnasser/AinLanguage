#pragma once
#include <iostream>
#include "AinException.hpp"

class OutOfRangeException:public AinException{

    public:
    OutOfRangeException(int lineNumber,std::wstring val)
    :AinException(
        AinException::errorWString(
            L"في السطر "+std::to_wstring(lineNumber)+
            L"\n"+
            val+
            L" القيمة خارج النطاق المسموح به."
        )
    ){}
};
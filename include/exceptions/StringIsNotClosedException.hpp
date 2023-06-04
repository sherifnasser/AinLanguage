#pragma once
#include <iostream>
#include "AinException.hpp"

class StringIsNotClosedException:public AinException{

    public:
    StringIsNotClosedException(int lineNumber,std::wstring strLiteral)
    :AinException(
        AinException::errorWString(
            L"في السطر "+std::to_wstring(lineNumber)+
            L" عند "+strLiteral+
            L"\n"+L"لم يتم إغلاق النص بعلامة تنصيص"
        )
    ){}
};
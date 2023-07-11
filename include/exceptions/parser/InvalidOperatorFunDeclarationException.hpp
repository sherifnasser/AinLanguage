#pragma once
#include "AinException.hpp"
#include <string>
class InvalidOperatorFunDeclarationException:public AinException{
    public:
    int lineNumber;
    InvalidOperatorFunDeclarationException(
        int lineNumber,
        std::wstring reason
    ):AinException(
        AinException::errorWString(
            L"في السطر "+std::to_wstring(lineNumber)+L"\n"+
            L"دالة مؤثر غير صالحة: "+reason
        )
    ),lineNumber(lineNumber){}
};
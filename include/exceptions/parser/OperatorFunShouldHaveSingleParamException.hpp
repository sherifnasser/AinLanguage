#pragma once
#include "AinException.hpp"
#include <string>
class OperatorFunShouldHaveSingleParamException:public AinException{
    public:
    int lineNumber;
    OperatorFunShouldHaveSingleParamException(
        int lineNumber
    ):AinException(
        AinException::errorWString(
            AinException::betweenAngleBrackets(
                L"دالة معامل"
            )
            +L" يجب أن تكون ذات مُدخَل واحد فقط."
        )
    ),lineNumber(lineNumber){}
};
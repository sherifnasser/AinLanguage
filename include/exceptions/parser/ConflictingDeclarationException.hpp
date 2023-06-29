#pragma once
#include "AinException.hpp"
#include <string>
class ConflictingDeclarationException:public AinException{
    public:
    int lineNumber;
    ConflictingDeclarationException(
        int lineNumber
    ):AinException(
        L"يوجد إعادة تعريف بنفس الاسم."
    ),lineNumber(lineNumber){}
};
#pragma once
#include <iostream>
#include <string>
#include "AinException.hpp"

class FunctionNotFoundException:public AinException{

    public:
    FunctionNotFoundException(std::wstring decl)
    :AinException(
        AinException::errorWString(
            L"لم يتم العثور على دالة ."+decl
        )
    ){}
};
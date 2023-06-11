#pragma once
#include <iostream>
#include "AinException.hpp"

class MainFunctionNotFoundException:public AinException{

    public:
    MainFunctionNotFoundException()
    :AinException(
        AinException::errorWString(
            L"لم يتم العثور على دالة البداية."
        )
    ){}
};
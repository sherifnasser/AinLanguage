#pragma once
#include <iostream>
#include "AinException.hpp"

class MissingQouteException:public AinException{

    public:
    MissingQouteException(int lineNumber,std::wstring literal)
    :AinException(
        AinException::errorWString(
            L"في السطر "+std::to_wstring(lineNumber)+
            L" عند "+literal+
            L"\n"+L"توجد علامة تنصيص مفقودة."
        )
    ){}
};
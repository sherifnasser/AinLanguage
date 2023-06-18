#pragma once
#include <iostream>
#include "AinException.hpp"

class ContainsKufrOrUnsupportedCharacterException:public AinException{

    public:
    ContainsKufrOrUnsupportedCharacterException(int lineNumber,std::wstring line)
    :AinException(
        AinException::errorWString(
            ((lineNumber>=0)?L"في السطر "+std::to_wstring(lineNumber)+L"\n":L"")+
            line+
            L"\n"+
            L"يحتوي على رمز للكُفار أو رمز غير مدعوم."
        )
    ){}
};
#include <iostream>
#include <string>
#include <algorithm>
#include "string_helper.hpp"
bool startsWith(std::string str, std::string prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

bool endsWith(std::string str, std::string suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

void removeUnderscores(std::wstring* wstr){
    wstr->erase(
        std::remove_if(
            wstr->begin(),
            wstr->end(),
            [](auto c){return c==L'_';}
        ),
        wstr->end()
    );
}

wchar_t getUnicodeCharacterFromCode(std::wstring codePoint){
    auto allDigits=std::all_of(codePoint.begin(), codePoint.end(), ::iswxdigit);
    if(codePoint.size()!=4||!allDigits)
        std::__throw_invalid_argument("Invalid universal charcater code.");
    auto uniCharInt=std::stoi(codePoint,0,16);
    auto uniChar=static_cast<wchar_t>(uniCharInt);
    return uniChar;
}

wchar_t getEscapeSequenceFromCharacter(const wchar_t& c){
    switch(c){
        // مسافة للخلف
        case L'خ' :return L'\b';

        // مساحة أفقية
        case L'ف' :return L'\t';

        // سطر جديد
        case L'س' :return L'\n';

        // مساحة رأسية
        case L'ر' :return L'\v';

        // الصفحة التالية
        case L'ص' :return L'\f';

        // إرجاع المؤشر إلى بداية السطر، وبدء الكتابة منه
        case L'ج' :return L'\r';
        
        case L'\\':return L'\\';
        case L'\"':return L'\"';
        case L'\'':return L'\'';
        default:
            std::__throw_invalid_argument("Invalid escape sequence.");
    }
}
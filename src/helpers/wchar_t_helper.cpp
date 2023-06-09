#include <iostream>
#include "wchar_t_helper.hpp"
#include "LexerToken.hpp"

bool isainpunct(const wchar_t &c)
{
    return (std::iswpunct(c)&&c!=L'_')
        ||c==L'؟'
        ||c==L'؛'
        ||c==L'،'
    ;
}

bool isainalpha(const wchar_t &c)
{
    return !isainpunct(c)&&!std::iswdigit(c)&&!iswempty(c)&&c!=L'\0';
}

bool iswempty(const wchar_t &c)
{
    return std::iswspace(c)||std::iswblank(c);
}

bool ispower10literaloperator(const wchar_t &c)
{
    return c==L'E'||c==L'e';
}

bool iswbdigit(const wchar_t &c){
    return c==L'0' || c==L'1';
}

bool iswodigit(const wchar_t &c){
    return c>=L'0' && c<=L'7';
}

bool isnumsystemchar(const wchar_t &c){
    return c==L'x'||c==L'X'||c==L'b'||c==L'B'||c==L'o'||c==L'O';
}
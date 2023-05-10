#include <iostream>
#include "wchar_t_helper.hpp"
#include "lexertoken.hpp"

bool isainpunct(wchar_t &c)
{
    return (std::iswpunct(c)&&c!=L'_')
        ||c==lexertoken::QUESTION_MARK
        ||c==lexertoken::SEMICOLON
        ||c==lexertoken::COMMA
    ;
}

bool isainalpha(wchar_t &c)
{
    return !isainpunct(c)&&!std::iswdigit(c)&&!iswempty(c);
}

bool iswempty(wchar_t &c)
{
    return std::iswspace(c)||std::iswblank(c);
}

bool ispower10literaloperator(wchar_t &c)
{
    return c==L'E'||c==L'e';
}

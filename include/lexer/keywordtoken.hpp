#pragma once
#include <iostream>
#include "lexertoken.hpp"
class keywordtoken:public lexertoken
{
    
public:
    keywordtoken(wstring val);
    static bool iskeyword(wstring val);
    static bool iskeyword(lexertoken t);
    static keywordtoken VAR;
    static keywordtoken VAL;
    static keywordtoken FUN;
    static keywordtoken RETURN;

    static keywordtoken PACKAGE;
    static keywordtoken IMPORT;
    static keywordtoken CLASS;
    static keywordtoken INTERFACE;
    static keywordtoken OBJECT;

    static keywordtoken DATA;
    static keywordtoken ABSTRACT;
    static keywordtoken OPEN;
    static keywordtoken ENUM;
    static keywordtoken ANNOTATION;

    static keywordtoken PUBLIC;
    static keywordtoken PRIVATE;
    static keywordtoken PROTECTED;
    static keywordtoken OVERRIDE;

    static keywordtoken IF;
    static keywordtoken ELSE_IF;
    static keywordtoken ELSE;
    static keywordtoken WHEN; // as switch

    static keywordtoken FOR;
    static keywordtoken WHILE;
    static keywordtoken BREAK;
    static keywordtoken CONTINUE;

    static keywordtoken THROW;
    static keywordtoken TRY;
    static keywordtoken CATCH;
    static keywordtoken FINALLY;
    
    // We may consider them as bool literal tokens, but we put them here instead
    static keywordtoken TRUE;
    static keywordtoken FALSE;
};
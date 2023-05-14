#include <iostream>
#include "keywordtoken.hpp"

keywordtoken::keywordtoken(wstring val):
lexertoken(lexertoken::KEYWORD_TOKEN,val){}

bool keywordtoken::iskeyword(lexertoken t){
    keywordtoken keywords[]={
        VAR,VAL,FUN,RETURN,
        PACKAGE,IMPORT,CLASS,INTERFACE,OBJECT,
        DATA,ABSTRACT,OPEN,ENUM,ANNOTATION,
        PUBLIC,PRIVATE,PROTECTED,OVERRIDE,
        IF,ELSE_IF,ELSE,WHEN,
        FOR,WHILE,BREAK,CONTINUE,
        THROW,TRY,CATCH,FINALLY,
    };

    for(keywordtoken &k:keywords){
        if(t==k)
            return true;
    }
    return false;
}

bool keywordtoken::iskeyword(wstring val){
    return iskeyword(keywordtoken(val));
}

keywordtoken keywordtoken::VAR=keywordtoken(L"متغير");
keywordtoken keywordtoken::VAL=keywordtoken(L"ثابت");
keywordtoken keywordtoken::FUN=keywordtoken(L"دالة");
keywordtoken keywordtoken::RETURN=keywordtoken(L"بقيمة");

keywordtoken keywordtoken::PACKAGE=keywordtoken(L"رزمة");
keywordtoken keywordtoken::IMPORT=keywordtoken(L"استيراد");
keywordtoken keywordtoken::CLASS=keywordtoken(L"طراز");
keywordtoken keywordtoken::INTERFACE=keywordtoken(L"وسيط");
keywordtoken keywordtoken::OBJECT=keywordtoken(L"كائن");

keywordtoken keywordtoken::DATA=keywordtoken(L"بيانات");
keywordtoken keywordtoken::ABSTRACT=keywordtoken(L"مجرد");
keywordtoken keywordtoken::OPEN=keywordtoken(L"مفتوح");
keywordtoken keywordtoken::ENUM=keywordtoken(L"سرد");
keywordtoken keywordtoken::ANNOTATION=keywordtoken(L"حاشية");

keywordtoken keywordtoken::PUBLIC=keywordtoken(L"تعميم");
keywordtoken keywordtoken::PRIVATE=keywordtoken(L"تخصيص");
keywordtoken keywordtoken::PROTECTED=keywordtoken(L"حماية");
keywordtoken keywordtoken::OVERRIDE=keywordtoken(L"هيمنة");

keywordtoken keywordtoken::IF=keywordtoken(L"لو");
keywordtoken keywordtoken::ELSE_IF=keywordtoken(L"لكن لو");
keywordtoken keywordtoken::ELSE=keywordtoken(L"وإلا");
keywordtoken keywordtoken::WHEN=keywordtoken(L"عندما"); // as switch

keywordtoken keywordtoken::FOR=keywordtoken(L"لأجل");
keywordtoken keywordtoken::WHILE=keywordtoken(L"طالما");
keywordtoken keywordtoken::BREAK=keywordtoken(L"اكسر");
keywordtoken keywordtoken::CONTINUE=keywordtoken(L"استكمل");

keywordtoken keywordtoken::THROW=keywordtoken(L"خطأ");
keywordtoken keywordtoken::TRY=keywordtoken(L"جرب");
keywordtoken keywordtoken::CATCH=keywordtoken(L"عالج");
keywordtoken keywordtoken::FINALLY=keywordtoken(L"بالنهاية");
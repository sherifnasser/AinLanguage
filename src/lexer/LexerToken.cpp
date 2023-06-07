#include <iostream>
#include "LexerToken.hpp"
#include "KeywordToken.hpp"
#include "number_helper.hpp"

LexerToken::LexerToken(){
    LexerToken(NOT_SET_TOKEN,L"");
}

LexerToken::LexerToken(TOKEN_TYPE tokenType, std::wstring val):tokenType(tokenType),val(val){}

LexerToken::TOKEN_TYPE LexerToken::getTokenType(){
    return this->tokenType;
}

std::wstring LexerToken::getVal(){
    return this->val;
}

bool LexerToken::operator==(LexerToken &token) const{
    return
    this->tokenType==token.getTokenType()
    &&
    this->val==token.getVal();
}

bool LexerToken::operator!=(LexerToken &token) const{
    return !(*this==token);
}

bool LexerToken::isidentifiertoken(){
    return this->getTokenType()==LexerToken::IDENTIFIER_TOKEN;
}

bool LexerToken::isnotsettoken(){
    return this->getTokenType()==LexerToken::NOT_SET_TOKEN;
}

bool LexerToken::isintliteral(){
    return isint(getVal());
}

bool LexerToken::islongliteral(){
    return islong(getVal());
}

bool LexerToken::isfloatliteral(){
    return isfloat(getVal());
}

bool LexerToken::isdoubleliteral(){
    return isdouble(getVal());
}

bool LexerToken::isnumberliteral(){
    return
        isintliteral()||
        islongliteral()||
        isfloatliteral()||
        isdoubleliteral()
    ;
}

bool LexerToken::ischarliteral(){
    return getVal().size()==1;
}

bool LexerToken::isstringliteral(){
    auto _val=getVal();
    wchar_t start=_val[0];
    wchar_t end=_val[val.size()-1];
    return start==end&&start==L'\"';
}

LexerToken LexerToken::identifiertoken = LexerToken(LexerToken::IDENTIFIER_TOKEN,L"");

LexerToken LexerToken::notsettoken = LexerToken();

LexerToken::~LexerToken(){}
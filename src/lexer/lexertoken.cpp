#include <iostream>
#include "lexertoken.hpp"
#include "keywordtoken.hpp"

lexertoken::lexertoken(TOKEN_TYPE tokentype, std::wstring val):tokentype(tokentype),val(val){}

lexertoken::TOKEN_TYPE lexertoken::gettokentype(){
    return this->tokentype;
}

std::wstring lexertoken::getval(){
    return this->val;
}

bool lexertoken::operator==(lexertoken &token){
    return
    this->gettokentype()==token.gettokentype()
    &&
    this->getval()==token.getval();
}

bool lexertoken::operator!=(lexertoken &token){
    return !(*this==token);
}

bool lexertoken::isidentifiertoken(){
    return this->gettokentype()==lexertoken::IDENTIFIER_TOKEN;
}

bool lexertoken::isnotsettoken(){
    return this->gettokentype()==lexertoken::NOT_SET_TOKEN;
}

lexertoken lexertoken::identifiertoken = lexertoken(lexertoken::IDENTIFIER_TOKEN,L"");

lexertoken lexertoken::notsettoken = lexertoken(lexertoken::NOT_SET_TOKEN,L"");
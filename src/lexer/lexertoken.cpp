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
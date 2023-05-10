#include <iostream>
#include "lexertoken.hpp"

lexertoken::lexertoken(TOKEN_TYPE tokentype, std::wstring &val):tokentype(tokentype),val(val){}

lexertoken::TOKEN_TYPE lexertoken::gettokentype(){
    return this->tokentype;
}

std::wstring lexertoken::getval(){
    return this->val;
}

bool lexertoken::iskeyword(){
    return iskeyword(val);
}

bool lexertoken::iskeyword(std::wstring &val){
    for(auto &k:TOKENS::KEYWORDS){
        if(k.second==val)
            return true;
    }
    return false;
}
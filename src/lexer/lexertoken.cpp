#include <iostream>
#include "lexertoken.hpp"
#include "keywordtoken.hpp"
#include "number_helper.hpp"

lexertoken::lexertoken(){
    lexertoken(NOT_SET_TOKEN,L"");
}

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

bool lexertoken::isintliteral(){
    return isint(getval());
}

bool lexertoken::islongliteral(){
    return islong(getval());
}

bool lexertoken::isfloatliteral(){
    return isfloat(getval());
}

bool lexertoken::isdoubleliteral(){
    return isdouble(getval());
}

bool lexertoken::isnumberliteral(){
    return
        isintliteral()||
        islongliteral()||
        isfloatliteral()||
        isdoubleliteral()
    ;
}

bool lexertoken::ischarliteral(){
    return getval().size()==1;
}

bool lexertoken::isstringliteral(){
    auto _val=getval();
    wchar_t start=_val[0];
    wchar_t end=_val[val.size()-1];
    return start==end&&start==L'\"';
}

lexertoken lexertoken::identifiertoken = lexertoken(lexertoken::IDENTIFIER_TOKEN,L"");

lexertoken lexertoken::notsettoken = lexertoken();
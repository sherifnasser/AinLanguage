#include <iostream>
#include "lexertoken.hpp"
#include "keywordtoken.hpp"

lexertoken::lexertoken(){
    lexertoken(NOT_SET_TOKEN,L"");
}

lexertoken::lexertoken(TOKEN_TYPE tokentype, wstring val):tokentype(tokentype),val(val){}

lexertoken::TOKEN_TYPE lexertoken::gettokentype(){
    return this->tokentype;
}

wstring lexertoken::getval(){
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
    try{
        int val=std::stoi(getval());
        return true;
    }catch(std::exception e){
        return false;
    }
}

bool lexertoken::islongliteral(){
    try{
        float val=std::stol(getval());
        return true;
    }catch(std::exception e){
        return false;
    }
}

bool lexertoken::isfloatliteral(){
    try{
        float val=std::stof(getval());
        return true;
    }catch(std::exception e){
        return false;
    }
}

bool lexertoken::isdoubleliteral(){
    try{
        double val=std::stod(getval());
        return true;
    }catch(std::exception e){
        return false;
    }
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
    wstring start=L""+_val[0];
    wstring end=L""+_val[val.size()-1];
    return start==end&&start==L"\"";
}

lexertoken lexertoken::identifiertoken = lexertoken(lexertoken::IDENTIFIER_TOKEN,L"");

lexertoken lexertoken::notsettoken = lexertoken();
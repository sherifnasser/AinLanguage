#include <iostream>
#include "LexerToken.hpp"
#include "KeywordToken.hpp"
#include "number_helper.hpp"
#include "NumberToken.hpp"
#include "LiteralToken.hpp"

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

bool LexerToken::isNumberLiteral(SharedLexerToken token){
    auto numToken=std::dynamic_pointer_cast<NumberToken>(token);
    return numToken!=nullptr;
}

bool LexerToken::isStringLiteral(SharedLexerToken token){
    auto stringToken=std::dynamic_pointer_cast<LiteralToken>(token);
    return stringToken!=nullptr && stringToken->getLiteralType()==LiteralToken::STRING;
}

LexerToken::~LexerToken(){}
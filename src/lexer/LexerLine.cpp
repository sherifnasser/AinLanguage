#include<iostream>
#include<memory>
#include<vector>
#include "LexerLine.hpp"
#include "LiteralToken.hpp"
#include "SymbolToken.hpp"
#include "wchar_t_helper.hpp"
#include "StringIsNotClosedException.hpp"

LexerLine::LexerLine(std::wstring &line,int lineNumber):line(line),lineNumber(lineNumber){
    this->tokens=std::make_shared<std::vector<std::shared_ptr<LexerToken>>>();
}

std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> LexerLine::getTokens(){
    return this->tokens;
}

int LexerLine::getLineNumber(){
    return this->lineNumber;
}

bool LexerLine::isNotNullToken(std::shared_ptr<LexerToken> token){
    if(token==nullptr)
        return false;
    tokens->push_back(token);
    return true;
}

void LexerLine::tokenize(){
    int i=0;
    while(i<line.size()){
        
        auto stringToken=findStringLiteralToken(&i);
        if(isNotNullToken(stringToken))
            continue;
        
        auto commentToken=findCommentToken(&i);
        if(isNotNullToken(commentToken))
            continue;
        
        auto symbolToken=findSymbolToken(&i);
        if(isNotNullToken(symbolToken))
            continue;
    }
}

std::shared_ptr<LexerToken> LexerLine::findStringLiteralToken(int* startIndex){
    
    auto &c=line[*startIndex];
    auto DOUBLE_QOUTE=L'\"';
    std::wstring CNTRL_DOUBLE_QOUTE=L"\\\""; // when there is double qoute inside the string

    if(c!=DOUBLE_QOUTE)
        return nullptr;

    std::wstring word=L"\"";  // add current "
    int i=++(*startIndex);
    // append every char in the line until finding another "

    while(i<line.size()){

        auto nextCnrtlDoubleQouteIndex=line.find(CNTRL_DOUBLE_QOUTE,i);

        if(nextCnrtlDoubleQouteIndex != std::wstring::npos){
            i=nextCnrtlDoubleQouteIndex+2; // get the char after \" (after 2 chars)
            continue;
        }

        // no more cntrl \" in the string

        auto lastDoubleQouteIndex=line.find(DOUBLE_QOUTE,i);  

        if(lastDoubleQouteIndex == std::wstring::npos){ // string isn't closed
            break;
        }

        word+=line.substr(*startIndex,lastDoubleQouteIndex-*startIndex+1);
        auto token=std::make_shared<LiteralToken>(LiteralToken::STRING,word);
        *startIndex=lastDoubleQouteIndex+1;
        return token;
    }

    word+=line.substr(*startIndex);
    throw StringIsNotClosedException(lineNumber,word);
}

std::shared_ptr<LexerToken> LexerLine::findCommentToken(int* startIndex){

    auto commentIndex=line.find(L"//",*startIndex);

    if(commentIndex!=*startIndex)
        return nullptr;
    
    auto word=line.substr(commentIndex);
    auto token=std::make_shared<LexerToken>(LexerToken::COMMENT_TOKEN,word);
    *startIndex=line.size();  // end of the line, so it'll stop the loop
    return token;
}


std::shared_ptr<LexerToken> LexerLine::findSymbolToken(int* startIndex){
    
    // find a double-symbol token (>=, <=, ==, !=, &&, ||) also assignment operators
    SymbolToken doubleSymbolTokens[]={
        SymbolToken::GREATER_EQUAL,
        SymbolToken::LESS_EQUAL,
        SymbolToken::EQUAL_EQUAL,
        SymbolToken::NOT_EQUAL,
        SymbolToken::LOGICAL_AND,
        SymbolToken::LOGICAL_OR,
        SymbolToken::PLUS_EQUAL,
        SymbolToken::MINUS_EQUAL,
        SymbolToken::STAR_EQUAL,
        SymbolToken::SLASH_EQUAL,
        SymbolToken::MODULO_EQUAL,
        SymbolToken::POWER_EQUAL
    };
    for(auto &s:doubleSymbolTokens){
        auto found=line.find(s.getVal(),*startIndex);
        if(found!=*startIndex)
            continue;
        *startIndex+=2; // skip next symbol
        auto token=std::make_shared<SymbolToken>(s);
        return token;
    }

    // find a single-symbol token
    auto &c=line[*startIndex];
    if(!isainpunct(c)) // This excludes underscore
        return nullptr;
    
    ++(*startIndex);
    std::wstring val;
    val=c;
    auto token=std::make_shared<SymbolToken>(val);
    return token;
}
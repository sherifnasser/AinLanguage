#include<iostream>
#include<memory>
#include<vector>
#include "LexerLine.hpp"
#include "LiteralToken.hpp"
#include "symboltoken.hpp"
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

void LexerLine::tokenize(){
    for(int i=0;i<line.size();i++){
        i=findStringLiteralToken(i);
    }
}

int LexerLine::findStringLiteralToken(int startIndex){
        
    auto &c=line[startIndex];
    auto DOUBLE_QOUTE=L'\"';
    std::wstring CNTRL_DOUBLE_QOUTE=L"\\\""; // when there is double qoute inside the string

    if(c!=DOUBLE_QOUTE)
        return startIndex;

    std::wstring word=L"\"";  // add current "
    int i=++startIndex;
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

        word+=line.substr(startIndex,lastDoubleQouteIndex-startIndex+1);
        auto token=std::make_shared<LiteralToken>(LiteralToken::STRING,word);
        tokens->push_back(token);
        return lastDoubleQouteIndex+1;
    }

    word+=line.substr(startIndex);
    throw StringIsNotClosedException(lineNumber,word);
}
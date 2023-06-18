#include <iostream>
#include "Lexer.hpp"
#include "LexerLine.hpp"
#include "string_helper.hpp"
#include "wchar_t_helper.hpp"
#include "KeywordToken.hpp"
#include "SymbolToken.hpp"

Lexer::Lexer(SharedIAinFile ainFile):ainFile(ainFile){
    lexerLines=std::make_shared<std::vector<SharedILexerLine>>();

    auto lines=ainFile->getLines();

    int lineNumber=0;

    for(auto &line:lines){
        lineNumber++;
        
        if(line.empty())
            continue;

        auto nextlexerline=std::make_shared<LexerLine>(line,lineNumber);
        nextlexerline->tokenize();
        lexerLines->push_back(nextlexerline);
        
    }

}

SharedVector<SharedILexerLine> Lexer::getLexerLines(){
    return lexerLines;
}

SharedVector<SharedLexerToken> Lexer::getTokens(){
    auto tokens=std::make_shared<std::vector<SharedLexerToken>>();
    for(auto &l:*lexerLines){
        auto ltokens=l->getTokens();
        tokens->insert(tokens->end(),ltokens->begin(),ltokens->end());
    }
    return tokens;
}
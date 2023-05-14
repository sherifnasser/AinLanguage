#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "ain_file.hpp"
#include "lexer.hpp"
#include "globalscope.hpp"
#include "parser.hpp"
#include "keywordtoken.hpp"
#include "symboltoken.hpp"

#define string std::string
#define vector std::vector
#define cout std::cout
#define endl std::endl

int main(int argc, char * argv[]){

    if(argc > 2){ // 2 as it includes the prgram name
        std::__throw_out_of_range("You can only pass one argumet for the ain file path.");
        return -1;
    }
        
    string path(argv[1]); // as it's the second arg
    
    //string p="/home/nasser/Projects/Programming/C++/AinLanguage/src/app_copy.ain";
    AinFile file=AinFile(path);
    lexer lex = lexer(file);
    auto lines=lex.getlexerlines();
    auto tokens=vector<lexertoken>{};
    for(auto &l:lines){
        auto ltokens=l.gettokens();
        tokens.insert(tokens.end(),ltokens->begin(),ltokens->end());
    }

    for(auto &t:tokens){
        std::wcout<<t.getval()<<L"\t"<<t.gettokentype()<<endl;
    }
    
    globalscope global;
    parser Parser(&tokens);
    Parser.startparse(global);
    std::wcout<<"END"<<endl;
    
    /* ----------------quick test---------------------
    auto type=lexertoken::IDENTIFIER_TOKEN;
    auto funname=lexertoken(type, L"main");
    auto funtype=lexertoken(type, L"Unit");
    auto p1=lexertoken(type, L"p1");
    auto p1t=lexertoken(type, L"p1T");
    auto p2=lexertoken(type, L"p2");
    auto p2t=lexertoken(type, L"p2T");
    auto p3=lexertoken(type, L"p3");
    auto p3t=lexertoken(type, L"p3T");
    auto p4=lexertoken(type, L"p4");
    auto p4t=lexertoken(type, L"p4T");
    auto tokens=vector<lexertoken>{
        keywordtoken::FUN,
        funname,
        symboltoken::RIGHT_PARENTHESIS,
            p1,symboltoken::COLON,p1t,symboltoken::COLON,
            p2,symboltoken::COLON,p2t,symboltoken::COLON,
            p3,symboltoken::COLON,p3t,symboltoken::COLON,
        symboltoken::LEFT_PARENTHESIS,
        symboltoken::COLON,
        funtype,
        symboltoken::RIGHT_CURLY_BRACES,
        symboltoken::LEFT_CURLY_BRACES,
    };

    parser p(tokens);
    p.startparse(globalscope());
    */
    return 0;
}
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

int main(){
    auto type=lexertoken::IDENTIFIER_TOKEN;
    auto funname=lexertoken(type, L"main");
    auto funtype=lexertoken(type, L"Unit");
    auto p1=lexertoken(type, L"p1");
    auto p1t=lexertoken(type, L"p1T");
    auto p2=lexertoken(type, L"p2");
    auto p2t=lexertoken(type, L"p2T");
    auto p3=lexertoken(type, L"p3");
    auto p3t=lexertoken(type, L"p3T");
    auto tokens=vector<lexertoken>{
        keywordtoken::FUN,
        funname,
        symboltoken::RIGHT_PARENTHESIS,
        symboltoken::LEFT_PARENTHESIS,
        symboltoken::RIGHT_CURLY_BRACES,
        symboltoken::LEFT_CURLY_BRACES,
    };

    parser p(tokens);
    p.startparse(globalscope());
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
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
    
    AinFile file=AinFile(path);
    lexer lex = lexer(file);
    auto lines=lex.getlexerlines();
    auto tokens=vector<lexertoken>{};
    for(auto &l:lines){
        auto ltokens=l.gettokens();
        tokens.insert(tokens.end(),ltokens->begin(),ltokens->end());
    }
    globalscope global;
    parser Parser(&tokens);
    Parser.startparse(&global);

    auto main=global.getmain();

    main->call();

    return 0;
}
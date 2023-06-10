#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "SharedPtrTypes.hpp"
#include "AinFile.hpp"
#include "Lexer.hpp"
#include "GlobalScope.hpp"
#include "FunScope.hpp"
#include "Parser.hpp"
#include "KeywordToken.hpp"
#include "SymbolToken.hpp"

#define string std::string
#define vector std::vector
#define wcout std::wcout
#define endl std::endl

int main(int argc, char * argv[]){

    if(argc > 2){ // 2 as it includes the prgram name
        std::__throw_out_of_range("You can only pass one argumet for the ain file path.");
        return -1;
    }

    string path(argv[1]); // as it's the second arg
    
    SharedIAinFile file=std::make_shared<AinFile>(path);
    SharedILexer lexer=std::make_shared<Lexer>(file);
    auto tokens=lexer->getTokens();
    SharedGlobalScope global=std::make_shared<GlobalScope>();
    auto parser=std::make_shared<Parser>();
    parser->startParse(tokens,global);
    auto main=global->getmain();

    main->call();

    return 0;
}
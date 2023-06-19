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


void readAndParse(std::string path, SharedGlobalScope global){
    SharedIAinFile file=std::make_shared<AinFile>(path);
    SharedILexer lexer=std::make_shared<Lexer>(file);
    auto tokens=lexer->getTokens();
    SharedIParser parser=std::make_shared<Parser>();
    parser->startParse(tokens,global);
}

int main(int argc, char * argv[]){

    // TODO: show info about ain and available options
    if(argc < 2){ // 2 as it includes the program name
        std::__throw_out_of_range("You should pass at least one ain file path.");
        return -1;
    }

    try{
        SharedGlobalScope global=std::make_shared<GlobalScope>();

        std::string mainPath(argv[1]); // default is first file

        // parse in reverse and make the main file at the end
        for(int i=argc-1;i>1;i--){
            if(argv[i-1]=="-m" || argv[i-1]=="--main")
                mainPath=std::string(argv[i]);
            else
                readAndParse(argv[i],global);
        }

        readAndParse(mainPath,global);

        auto main=global->getMain();

        main->call();
    }
    catch(std::exception& e){
        std::cout<<e.what()<<std::endl;
    }
    

    return 0;
}
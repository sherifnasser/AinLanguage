#include <iostream>
#include <stdexcept>
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

bool isMainFileOption(std::string o){
    return o=="-m" || o=="--main";
}

int main(int argc, char * argv[]){

    // TODO: show info about ain and available options
    if(argc < 2){ // 2 as it includes the program name
        std::__throw_out_of_range("You should pass at least one ain file path.");
        return -1;
    }

    try{
        SharedGlobalScope global=std::make_shared<GlobalScope>();

        // default is first file
        std::string mainPath(argv[1]);

        // to make sure that -m or --main is used only once 
        auto mainOptionUsed=false;

        // parse in reverse and make the main file at the end
        for(int i=argc-1;i>1;i--){
            if(isMainFileOption(argv[i-1])){
                if(mainOptionUsed)
                    throw std::invalid_argument("\033[1;31mأمر -m أو --main يجب أن يُستخدم مرة واحدة فقط.\033[0m");
                mainPath=std::string(argv[i]);
                mainOptionUsed=true;
                i--;
                continue;
            }
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
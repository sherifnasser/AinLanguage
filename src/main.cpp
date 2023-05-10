#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "ain_file.hpp"
#include "lexer.hpp"

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
    for(auto &l:lines){
        auto tokens=l.gettokens();
        cout<<"L"<<l.getlinenumber()<<"\t"<<"s"<<tokens->size()<<endl;
        for(auto &t:*tokens){
            std::wcout<<"\t"<<t.gettokentype()<<L"\t"<<t.getval()<<endl;
        }
    }

    return 0;
}
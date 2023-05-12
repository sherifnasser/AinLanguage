#include <iostream>
#include "parser.hpp"
#include "lexertoken.hpp"
#include "keywordtoken.hpp"
#include "symboltoken.hpp"
#define wstring std::wstring
#define cout std::cout
#define endl std::endl


parser::parser(std::vector<lexertoken> &tokens):tokens(tokens){}

void parser::startparse(globalscope globalscope){
    findglobalfunctions(globalscope);
}

void parser::findglobalfunctions(globalscope &globalscope){
    bool found=false;
    int i=0;
    for(i;i<tokens.size();i+=3){
        cout<<(tokens[i]==keywordtoken::FUN)<<endl;
        if(
            tokens[i]==keywordtoken::FUN
            &&
            tokens[i+1].gettokentype()==lexertoken::IDENTIFIER_TOKEN
            &&
            tokens[i+2]==symboltoken::RIGHT_PARENTHESIS
        ){
            for(i+=3;i<tokens.size();i+=4){
                auto &argname = tokens[i];
                auto &colon = tokens[i+1];
                auto &argtype = tokens[i+2];
                auto &commaOrLP = tokens[i+3];

                bool argnameAndargtypeAreIdentifiers=(
                    argname.gettokentype()
                    ==
                    lexertoken::IDENTIFIER_TOKEN
                    ==
                    argtype.gettokentype()
                );

                bool iscommaOrPL =
                    commaOrLP == symboltoken::COMMA ||
                    commaOrLP == symboltoken::LEFT_PARENTHESIS;

                if(argnameAndargtypeAreIdentifiers && colon==symboltoken::COLON || iscommaOrPL)
                {
                    std::wcout<<argname.getval()<<":"<<argtype.getval()<<endl;
                    if(commaOrLP == symboltoken::LEFT_PARENTHESIS){
                        auto &colonOrRCB = tokens[++i];

                        auto read_fun_body=[&i](auto &tokens){
                            auto num_of_opened_curly_braces=0;
                            if(tokens[i]==symboltoken::RIGHT_CURLY_BRACES){
                                for(i;i<tokens.size();i++){

                                    if(tokens[i]==symboltoken::LEFT_CURLY_BRACES){
                                        if(num_of_opened_curly_braces==0){
                                            std::wcout<<"END of the function"<<endl;
                                            break;
                                        }else{
                                            num_of_opened_curly_braces--;
                                        }
                                    }
                                    else if(tokens[i]==symboltoken::RIGHT_CURLY_BRACES){
                                        num_of_opened_curly_braces++;
                                    }
                                }
                            }
                        };

                        if(colonOrRCB==symboltoken::COLON){
                            auto funtype = tokens[++i];
                            if(funtype.gettokentype()==lexertoken::IDENTIFIER_TOKEN){
                                std::wcout<<"funtype: "<<funtype.getval()<<endl;
                                read_fun_body(tokens);
                            }
                        }else{
                            read_fun_body(tokens);
                        }
                        
                    }
                }
            }
        }
    }

}


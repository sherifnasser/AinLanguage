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

        auto read_fun_body = [&i](auto &tokens)
        {
            auto num_of_opened_curly_braces = 0;
            if (tokens[i] == symboltoken::RIGHT_CURLY_BRACES)
            {
                for (i; i < tokens.size(); i++)
                {

                    if (tokens[i] == symboltoken::LEFT_CURLY_BRACES)
                    {
                        if (num_of_opened_curly_braces == 0)
                        {
                            std::wcout << "END of the function" << endl;
                            break;
                        }
                        else
                        {
                            num_of_opened_curly_braces--;
                        }
                    }
                    else if (tokens[i] == symboltoken::RIGHT_CURLY_BRACES)
                    {
                        num_of_opened_curly_braces++;
                    }
                }
            }
        };

        auto read_colonOrRCB = [&i,&read_fun_body](auto &tokens)
        {
            auto &colonOrRCB = tokens[++i];

            if (colonOrRCB == symboltoken::COLON)
            {
                auto funtype = tokens[++i];
                if (funtype.gettokentype() == lexertoken::IDENTIFIER_TOKEN)
                {
                    std::wcout << "funtype: " << funtype.getval() << endl;
                    read_fun_body(tokens);
                }
            }
            else
            {
                read_fun_body(tokens);
            }
        };


        if(
            tokens[i]==keywordtoken::FUN
            &&
            tokens[i+1].gettokentype()==lexertoken::IDENTIFIER_TOKEN
            &&
            tokens[i+2]==symboltoken::RIGHT_PARENTHESIS
        ){
            std::wcout<<"funname: "<<tokens[i+1].getval()<<endl;
            for(i+=3;i<tokens.size();i+=4){
                auto &argnameOrLP = tokens[i];
                auto &colon = tokens[i+1];
                auto &argtype = tokens[i+2];
                lexertoken* commaOrLP;
                bool iscommaOrPL;
                try{
                    commaOrLP=&tokens[i+3];
                    iscommaOrPL =
                    *commaOrLP == symboltoken::COMMA ||
                    *commaOrLP == symboltoken::LEFT_PARENTHESIS;
                }catch(std::exception e){
                    
                }

                bool argnameAndargtypeAreIdentifiers=(
                    argnameOrLP.gettokentype()
                    ==
                    lexertoken::IDENTIFIER_TOKEN
                    ==
                    argtype.gettokentype()
                );

                if(argnameAndargtypeAreIdentifiers && colon==symboltoken::COLON || iscommaOrPL)
                {
                    std::wcout<<argnameOrLP.getval()<<":"<<argtype.getval()<<endl;
                    if(*commaOrLP == symboltoken::LEFT_PARENTHESIS){
                        i+=3;
                        read_colonOrRCB(tokens);
                    }
                }else if(argnameOrLP==symboltoken::LEFT_PARENTHESIS){
                    read_colonOrRCB(tokens);
                }
            }
        }
    }

}


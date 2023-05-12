#include <iostream>
#include "parser.hpp"
#include "lexertoken.hpp"
#include "keywordtoken.hpp"
#include "symboltoken.hpp"
#define wstring std::wstring
#define cout std::cout
#define wcout std::wcout
#define endl std::endl


parser::parser(std::vector<lexertoken>* tokensP){
    tokens=tokensP;
}

void parser::startparse(globalscope globalscope){
    findglobalfunctions(globalscope);
}

void parser::findglobalfunctions(globalscope &globalscope){
    auto notsettoken=lexertoken::notsettoken;
    int i=-1; // to make the next
    auto tokensR=tokens;
    lexertoken current=notsettoken;
    auto next=[&i,&notsettoken,&tokensR,&current](){
        ++i;
        current=(i<tokensR->size())? (*tokensR)[i]:notsettoken;
        //wcout<<current.getval()<<L"\t"<<current.gettokentype()<<endl;
        return current;
    };
    //next(); // to set a value to the current
    do{
        if(current==keywordtoken::FUN){
            if(next().isidentifiertoken()){
                auto funname=current.getval();
                if(next()==symboltoken::LEFT_PARENTHESIS){
                    wcout<<L"funname: "<<funname<<endl;
                    /*----------------we have two ways-------------------/*
                    1- the next token is left parenthesis and no args for the fun.
                    2- there're args in form (arg1:arg1Type, arg2:arg2Type, ...). */

                    while(next()!=symboltoken::RIGHT_PARENTHESIS){
                        if(current.isidentifiertoken()){
                            auto arg=current.getval();
                            if(next()==symboltoken::COLON){
                                if(next().isidentifiertoken()){
                                    auto argtype=current.getval();
                                    wcout<<arg<<L": "<<argtype<<endl;
                                    // calling next() first multi args without a comma
                                    if(next()==symboltoken::COMMA){}
                                    // the user may right the comma or not at the end
                                    else if(current==symboltoken::RIGHT_PARENTHESIS)
                                    {break;}
                                    // else error
                                }
                            }
                        } // else error
                    }
                    if(next()==symboltoken::COLON){
                        if(next().isidentifiertoken()){
                            wcout<<L"funtype: "<<current.getval()<<endl;
                            next();
                        }
                    }
                    if(current==symboltoken::LEFT_CURLY_BRACES){
                        auto openedCB=0; // the number of opened curly braces
                        while(next()!=symboltoken::RIGHT_CURLY_BRACES&&openedCB)
                        {
                            // TODO -> Parsing statements of the function
                            if(current==symboltoken::LEFT_CURLY_BRACES){openedCB++;}
                            else if(current==symboltoken::RIGHT_CURLY_BRACES){openedCB--;}
                        }
                        
                    }
                }
            }
        }
    }while(next()!=notsettoken);

}


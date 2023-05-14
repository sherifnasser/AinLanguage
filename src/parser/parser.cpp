#include <iostream>
#include <map>
#include "parser.hpp"
#include "lexertoken.hpp"
#include "keywordtoken.hpp"
#include "symboltoken.hpp"

#define notsettoken lexertoken::notsettoken
#define wcout std::wcout
#define endl std::endl


parser::parser(std::vector<lexertoken>* tokensP){
    tokens=tokensP;
    current=next();
}

lexertoken parser::next(){
    currentpos++;
    current=(currentpos<tokens->size())? (*tokens)[currentpos]:notsettoken;
    return current;
}

bool parser::currentmatch(lexertoken expected){
    return current==expected;
}

bool parser::nextmatch(lexertoken expected){
    next();
    return currentmatch(expected);
}

wstring parser::currentval(){
    return current.getval();
}

void parser::startparse(globalscope globalscope){
    /*while(current!=notsettoken){
        find_functions(globalscope);
    }*/

    expression* ex=find_binary_math_expression();
    wcout<<"Hi"<<endl;
    wstring s=L"";
    ex->print(s);
}

void parser::find_functions(globalscope &globalscope){
    wstring funname;
    wstring funtype=L"";
    std::map<wstring,wstring> args;
    if(currentmatch(keywordtoken::FUN)){
        if(next().isidentifiertoken()){
            funname=currentval();
            if(nextmatch(symboltoken::LEFT_PARENTHESIS)){
                wcout<<L"funname: "<<funname<<endl;
                /*----------------we have two ways-------------------/*
                1- the next token is left parenthesis and no args for the fun.
                2- there're args in form (arg1:arg1Type, arg2:arg2Type, ...). */
                while(!nextmatch(symboltoken::RIGHT_PARENTHESIS)){
                    if(current.isidentifiertoken()){
                        auto arg=currentval();
                        if(nextmatch(symboltoken::COLON)){
                            if(next().isidentifiertoken()){
                                auto argtype=currentval();
                                args[arg]=argtype;
                                wcout<<arg<<L": "<<argtype<<endl;
                                // calling next() first multi args without a comma
                                if(nextmatch(symboltoken::COMMA)){}
                                // the user may right the comma or not at the end
                                else if(current==symboltoken::RIGHT_PARENTHESIS)
                                {break;}
                                // else error
                            }
                        }
                    } // else error
                }

                if(nextmatch(symboltoken::COLON)){
                    if(next().isidentifiertoken()){
                        funtype=currentval();
                        wcout<<L"funtype: "<<currentval()<<endl;
                        next();
                    }
                }
                auto fun=[&](){
                    if(args.size()==0){
                        if(funtype.empty()){
                            return funscope(funname,&args);
                        }
                        else return funscope(funname);
                    }
                    else if(funtype.empty())
                        return funscope(funname,&args);
                    
                    else return funscope(funname);
                    
                };

                auto fscope=fun();
                globalscope.addfunction(fscope);


                if(current==symboltoken::LEFT_CURLY_BRACES){
                    auto openedCB=0; // the number of opened curly braces
                    while(!nextmatch(symboltoken::RIGHT_CURLY_BRACES)&&openedCB!=0)
                    {
                        // TODO -> Parsing statements of the function
                        if(current==symboltoken::LEFT_CURLY_BRACES){
                            openedCB++;
                            find_next_statement(fscope);
                        }
                        else if(current==symboltoken::RIGHT_CURLY_BRACES){openedCB--;}
                    }
                }
                // else error
            }
        }
    }
}

void parser::find_next_statement(funscope &funscope){    
    find_var_val_statement(funscope);
}

void parser::find_var_val_statement(funscope &funscope){
    auto isvar=currentmatch(keywordtoken::VAR);
    auto isval=currentmatch(keywordtoken::VAL);
    wstring name,type=L"";
    if(isvar||isval){
        if(next().isidentifiertoken()){
            name=currentval();
            if(nextmatch(symboltoken::COLON)){
                if(next().isidentifiertoken()){
                    type=currentval();
                    next();
                }
            }
            if(currentmatch(symboltoken::EQUAL)){
                next();
                find_expression();
            }
        }
    }
    
}

void parser::find_expression(){
    expression* math=find_binary_math_expression();
    find_expression();
}

expression* parser::find_binary_math_expression(){
    return find_binary_math_plus_minus_expression();
}

expression* parser::find_binary_math_plus_minus_expression(){
    expression* left=find_binary_math_star_slash_expression();
    expression* right;
    while(
        currentmatch(symboltoken::PLUS)
        ||
        currentmatch(symboltoken::MINUS)
    ){
        lexertoken op=current;
        next();
        right=find_binary_math_star_slash_expression();
        left=new binarymathxpression(left,op,right);
        //next();
    }
    return left;
    
}

expression* parser::find_binary_math_star_slash_expression(){
    expression* left=find_binary_math_exponent_expression();
    expression* right;
    while(
        currentmatch(symboltoken::STAR)
        ||
        currentmatch(symboltoken::SLASH)
        ||
        currentmatch(symboltoken::MODULO)
    ){
        lexertoken op=current;
        next();
        right=find_binary_math_exponent_expression();
        left=new binarymathxpression(left,op,right);
        //next();
    }
    return left;
}

expression* parser::find_binary_math_exponent_expression(){
    expression* left=find_binary_math_parentheses_expression();
    expression* right;
    while(currentmatch(symboltoken::POWER)){
        lexertoken op=current;
        next();
        right=find_binary_math_parentheses_expression();
        left=new binarymathxpression(left,op,right);
        //next();
    }
    return left;
}

expression* parser::find_binary_math_parentheses_expression(){
    expression* left;
    expression* right;
    if(currentmatch(symboltoken::LEFT_PARENTHESIS)){
        next();
        left=find_binary_math_plus_minus_expression();
        //next();
        while(!currentmatch(symboltoken::RIGHT_PARENTHESIS)){
            lexertoken op=current;
            next();
            right=find_binary_math_plus_minus_expression();
            left=new binarymathxpression(left,op,right);
            //next();next();
        }
        next();
    }
    else if(current.isnumberliteral()){
        auto val=currentval();
        left=new numberexpression(val);
        next();
    }
    //next();
    return left;
}
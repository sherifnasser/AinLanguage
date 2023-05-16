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
        next();
    }*/
    auto ex=find_expression();
    wstring tab=L"";
    ex->print(tab);
}

void parser::find_functions(globalscope &globalscope){
    wstring funname;
    wstring funtype=L"";
    std::vector<std::pair<wstring,wstring>>* args=new std::vector<std::pair<wstring,wstring>>();
    if(currentmatch(keywordtoken::FUN)){
        if(next().isidentifiertoken()){
            funname=currentval();
            if(nextmatch(symboltoken::LEFT_PARENTHESIS)){
                /*----------------we have two ways-------------------/*
                1- the next token is left parenthesis and no args for the fun.
                2- there're args in form (arg1:arg1Type, arg2:arg2Type, ...). */
                while(!nextmatch(symboltoken::RIGHT_PARENTHESIS)){
                    if(current.isidentifiertoken()){
                        auto argname=currentval();
                        if(nextmatch(symboltoken::COLON)){
                            if(next().isidentifiertoken()){
                                auto argtype=currentval();
                                auto arg=std::pair<wstring,wstring>(argname,argtype);
                                args->push_back(arg);
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
                        next();
                    }
                }   
                
                /*wcout<<L"funname: "<<funname<<endl;
                for(auto &arg:args){
                    wcout<<L"\t"<<arg.first<<L": "<<arg.second<<endl;
                }
                wcout<<L"funtype: "<<funtype<<endl;*/
                auto fscope=new funscope(funname,funtype,args);
                globalscope.addfunction(fscope);

                if(current==symboltoken::LEFT_CURLY_BRACES){
                    auto openedCB=0; // the number of opened curly braces
                    next();
                    while(!currentmatch(symboltoken::RIGHT_CURLY_BRACES))
                    {
                        find_next_statement(fscope);
                        /*// TODO -> Parsing statements of the function
                        if(current==symboltoken::LEFT_CURLY_BRACES){
                            openedCB++;
                        }
                        else if(current==symboltoken::RIGHT_CURLY_BRACES){openedCB--;}*/
                    }

                }
                // else error
            }
        }
    }
}

void parser::find_next_statement(funscope* funscope){    
    find_var_val_statement(funscope);
}

void parser::find_var_val_statement(funscope* funscope){
    auto isvar=currentmatch(keywordtoken::VAR);
    auto isval=currentmatch(keywordtoken::VAL);
    wstring name,type=L"";
    expression* ex;
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
                ex=find_expression();
                //wstring t=L"";
                //ex->print(t);
                //next();
            }
        }
    }
    scope* parentscope=funscope;
    if(isvar){
        variable* var;
        if(ex!=nullptr){
            if(type.empty()){
                var=new variable(parentscope,name,ex);
            }
                
            else{
                var=new variable(parentscope,name,type,ex);
            }
        }
        else{
            var=new variable(parentscope,name,type);
        }
        funscope->getvars()->push_back(*var);
    }
    else if(isval){
        constant* val;
        if(ex!=nullptr){
            if(type.empty()){
                val=new constant(parentscope,name,ex);
            }
                
            else{
                val=new constant(parentscope,name,type,ex);
            }
        }
        else{
            val=new constant(parentscope,name,type);
        }
        funscope->getvals()->push_back(*val);
    }
}

expression* parser::find_expression(){
    return find_binary_logical_or_expression();
}

expression* parser::find_binary_logical_or_expression(){
    expression* left=find_binary_logical_and_expression();
    expression* right;
    while(currentmatch(symboltoken::BAR)&&nextmatch(symboltoken::BAR))
    {   
        lexertoken op=symboltoken::LOGICAL_OR;
        next();
        right=find_binary_logical_and_expression();
        left=new binaryexpression(left,op,right);
    }
    return left;
    
}

expression* parser::find_binary_logical_and_expression(){
    expression* left=find_binary_equality_expression();
    expression* right;
    while(currentmatch(symboltoken::AMPERSAND)&&nextmatch(symboltoken::AMPERSAND))
    {   
        lexertoken op=symboltoken::LOGICAL_AND;
        next();
        right=find_binary_equality_expression();
        left=new binaryexpression(left,op,right);
    }
    return left;
    
}

expression* parser::find_binary_equality_expression(){
    expression* left=find_binary_comparison_expression();
    expression* right;
    while(currentmatch(symboltoken::EXCLAMATION_MARK)||currentmatch(symboltoken::EQUAL))
    {
        lexertoken op=current;
        if(nextmatch(symboltoken::EQUAL)){
            op=lexertoken(lexertoken::SYMBOL_TOKEN,op.getval()+L"="); // we don't need if() to make op != or ==
            next();
            right=find_binary_comparison_expression();
            left=new binaryexpression(left,op,right);
        }
        // else error
    }
    return left;
    
}

expression* parser::find_binary_comparison_expression(){
    expression* left=find_binary_math_plus_minus_expression();
    expression* right;
    while(
        currentmatch(symboltoken::LEFT_ANGLE_BRACKET)
        ||
        currentmatch(symboltoken::RIGHT_ANGLE_BRACKET)
    ){
        lexertoken op=current;
        if(nextmatch(symboltoken::EQUAL)){
            op=lexertoken(lexertoken::SYMBOL_TOKEN,op.getval()+L"="); // we don't need if() to make op >= or <=
            next();
        }
        right=find_binary_math_plus_minus_expression();
        left=new binaryexpression(left,op,right);
    }
    return left;
    
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
        left=new binaryexpression(left,op,right);
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
        left=new binaryexpression(left,op,right);
    }
    return left;
}

expression* parser::find_binary_math_exponent_expression(){
    expression* left=find_binary_parentheses_expression();
    expression* right;
    while(currentmatch(symboltoken::POWER)){
        lexertoken op=current;
        next();
        right=find_binary_parentheses_expression();
        left=new binaryexpression(left,op,right);
    }
    return left;
}

expression* parser::find_binary_parentheses_expression(){
    expression* left;
    expression* right;
    if(currentmatch(symboltoken::LEFT_PARENTHESIS)){
        next();
        left=find_binary_logical_or_expression();
        while(!currentmatch(symboltoken::RIGHT_PARENTHESIS)){
            lexertoken op=current;
            next();
            right=find_binary_logical_or_expression();
            left=new binaryexpression(left,op,right);
        }
        next();
    }
    else if(current.isnumberliteral()){
        auto val=currentval();
        left=new numberexpression(val);
        next();
    }
    else if(current.isidentifiertoken()){
        auto name=currentval();
        if(nextmatch(symboltoken::LEFT_PARENTHESIS)){
            next();
            auto argsex=new std::vector<expression*>();
            while(!currentmatch(symboltoken::RIGHT_PARENTHESIS)){
                auto argex=find_expression();
                argsex->push_back(argex);
                if(currentmatch(symboltoken::COMMA)){
                    next();
                }
            }
            left=new funcallexpression(name,argsex);
            next();
        }
        else{
            left=new variableaccessexpression(name);
        }
    }
    return left;
}
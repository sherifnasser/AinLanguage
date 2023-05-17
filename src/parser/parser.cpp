#include <iostream>
#include <map>
#include "parser.hpp"
#include "lexertoken.hpp"
#include "keywordtoken.hpp"
#include "symboltoken.hpp"
#include "statement.hpp"

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
    // skip comments
    if(current.gettokentype()!=lexertoken::COMMENT_TOKEN)
        return current;
    else
        return next();
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

void parser::startparse(globalscope* globalscope){
    while(current!=notsettoken){
        find_functions(globalscope);
        next();
    }
    /*auto ex=find_expression();
    wstring tab=L"";
    ex->print(tab);*/
}

void parser::find_functions(globalscope* globalscope){
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
                
                auto fscope=new funscope(globalscope,funname,funtype,args);
                globalscope->addfunction(fscope);

                if(current==symboltoken::LEFT_CURLY_BRACES){
                    auto openedCB=0; // the number of opened curly braces
                    next();
                    while(!currentmatch(symboltoken::RIGHT_CURLY_BRACES))
                    {
                        find_next_statement(fscope);
                    }

                }
                // else error
            }
        }
    }
}

void parser::find_next_statement(funscope* fscope){    
    if(find_var_val_statement(fscope)==nullptr){
        if(find_var_reassign_statement(fscope)==nullptr){
            if(find_return_statement(fscope)==nullptr){
                find_expression_statement(fscope);
            }
        }
    }
}

statement* parser::find_return_statement(funscope* fscope){
    if(currentmatch(keywordtoken::RETURN)){
        next();
        //next();
        auto ex=find_expression();
        //wcout<<L"WELCOME"<<endl;
        auto stm=new returnstatement(fscope,ex);
        fscope->getstmlist()->push_back(stm);
        return stm;
    }
    return nullptr;
}

statement* parser::find_expression_statement(funscope* fscope){
    auto ex=find_expression();
    auto stm=new expressionstatement(fscope,ex);
    //wstring tab=L"";
    //ex->print(tab);
    fscope->getstmlist()->push_back(stm);
    return stm;
}

statement* parser::find_var_reassign_statement(funscope* fscope){
    if(current.isidentifiertoken()){
        auto varname=current.getval();
        if(nextmatch(symboltoken::EQUAL)){
            next();
            auto ex=find_expression();
            auto stm=new varreassignstatement(fscope,varname,ex);
            fscope->getstmlist()->push_back(stm);
            return stm;
        }else{
            currentpos-=2;
            next();
        }
    }
    return nullptr;
}

statement* parser::find_var_val_statement(funscope* fscope){
    auto isvar=currentmatch(keywordtoken::VAR);
    auto isval=currentmatch(keywordtoken::VAL);
    wstring name,type=L"";
    expression* ex=nullptr;     
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
            }
            variable* var;
            if(isvar){
                var=new variable(fscope,name,type);
            }
            else if(isval){
                var=new constant(fscope,name,type);
            }
            auto stm=new vardeclarationstatement(fscope,var,ex);
            fscope->getstmlist()->push_back(stm);
            return stm;
        }
    }
    return nullptr;
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
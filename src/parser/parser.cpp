#include <iostream>
#include <map>
#include "parser.hpp"
#include "LexerToken.hpp"
#include "KeywordToken.hpp"
#include "SymbolToken.hpp"
#include "statement.hpp"

#define notsettoken LexerToken::notsettoken
#define wcout std::wcout
#define endl std::endl


parser::parser(std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> tokensP){
    tokens=tokensP;
    current=next();
}

LexerToken parser::next(){
    currentpos++;
    current=(currentpos<tokens->size())?(*((*tokens)[currentpos])):notsettoken;
    // skip comments
    if(current.getTokenType()!=LexerToken::COMMENT_TOKEN)
        return current;
    else
        return next();
}

bool parser::currentmatch(LexerToken expected){
    return current==expected;
}

bool parser::nextmatch(LexerToken expected){
    next();
    return currentmatch(expected);
}

std::wstring parser::currentval(){
    return current.getVal();
}

void parser::startparse(globalscope* globalscope){
    while(current!=notsettoken){
        find_functions(globalscope);
        next();
    }
    /*auto ex=find_expression();
    std::wstring tab=L"";
    ex->print(tab);*/
}

void parser::find_functions(globalscope* globalscope){
    std::wstring funname;
    std::wstring funtype=L"";
    std::vector<std::pair<std::wstring,std::wstring>>* args=new std::vector<std::pair<std::wstring,std::wstring>>();
    if(currentmatch(KeywordToken::FUN)){
        if(next().isidentifiertoken()){
            funname=currentval();
            if(nextmatch(SymbolToken::LEFT_PARENTHESIS)){
                /*----------------we have two ways-------------------/*
                1- the next token is left parenthesis and no args for the fun.
                2- there're args in form (arg1:arg1Type, arg2:arg2Type, ...). */
                while(!nextmatch(SymbolToken::RIGHT_PARENTHESIS)){
                    if(current.isidentifiertoken()){
                        auto argname=currentval();
                        if(nextmatch(SymbolToken::COLON)){
                            if(next().isidentifiertoken()){
                                auto argtype=currentval();
                                auto arg=std::pair<std::wstring,std::wstring>(argname,argtype);
                                args->push_back(arg);
                                // calling next() first multi args without a comma
                                if(nextmatch(SymbolToken::COMMA)){}
                                // the user may right the comma or not at the end
                                else if(current==SymbolToken::RIGHT_PARENTHESIS)
                                {break;}
                                // else error
                            }
                        }
                    } // else error
                }

                if(nextmatch(SymbolToken::COLON)){
                    if(next().isidentifiertoken()){
                        funtype=currentval();
                        next();
                    }
                }   
                
                auto fscope=new funscope(globalscope,funname,funtype,args);
                globalscope->addfunction(fscope);

                if(current==SymbolToken::LEFT_CURLY_BRACES){
                    next();
                    while(!currentmatch(SymbolToken::RIGHT_CURLY_BRACES))
                        add_next_stm_to_stm_list(fscope,fscope->getstmlist());
                }
                // else error
            }
        }
    }
}

void parser::add_next_stm_to_stm_list(funscope* fscope,StmList* stmlist){
    auto stm=find_next_statement(fscope);
    if(stm!=nullptr)
        stmlist->push_back(stm);
}

statement* parser::find_next_statement(funscope* fscope){
    
    auto var_val_statement=find_var_val_statement(fscope);
    if(var_val_statement!=nullptr)
        return var_val_statement;
    
    auto var_reassign_statement=find_var_reassign_statement(fscope);
    if(var_reassign_statement!=nullptr)
        return var_reassign_statement;

    auto return_statement=find_return_statement(fscope);
    if(return_statement!=nullptr)
        return return_statement;
    
    auto if_statement=find_if_statement(fscope);
    if(if_statement!=nullptr)
        return if_statement;

    auto do_while_statement=find_do_while_statement(fscope);
    if(do_while_statement!=nullptr)
        return do_while_statement;

    auto while_statement=find_while_statement(fscope);
    if(while_statement!=nullptr)
        return while_statement;
        
    auto expression_statement=find_expression_statement(fscope);
    if(expression_statement!=nullptr)
        return expression_statement;

    return nullptr;
}

statement* parser::find_while_statement(funscope* fscope){
    if(currentmatch(KeywordToken::WHILE)&&nextmatch(SymbolToken::LEFT_PARENTHESIS)){
        next();
        auto ex=find_expression();
        if(currentmatch(SymbolToken::RIGHT_PARENTHESIS)){
            StmList* stmlist=new StmList();
            if(nextmatch(SymbolToken::LEFT_CURLY_BRACES)){
                next();
                while(!currentmatch(SymbolToken::RIGHT_CURLY_BRACES))
                    add_next_stm_to_stm_list(fscope,stmlist);
                next();
                    
            }else add_next_stm_to_stm_list(fscope,stmlist);

            auto while_statment=new whilestatement(fscope,ex,stmlist);
            return while_statment;
        }
    }
    return nullptr;
}

statement* parser::find_do_while_statement(funscope* fscope){
    if(currentmatch(KeywordToken::DO)){
        StmList* stmlist=new StmList();
        if(nextmatch(SymbolToken::LEFT_CURLY_BRACES)){
            next();
            while(!currentmatch(SymbolToken::RIGHT_CURLY_BRACES))
                add_next_stm_to_stm_list(fscope,stmlist);
            next();
                    
        }else add_next_stm_to_stm_list(fscope,stmlist);

        if(currentmatch(KeywordToken::WHILE)&&nextmatch(SymbolToken::LEFT_PARENTHESIS)){
            next();
            auto ex=find_expression();
            if(currentmatch(SymbolToken::RIGHT_PARENTHESIS)){
                next();
                auto do_while_statment=new dowhilestatement(fscope,ex,stmlist);
                return do_while_statment;
            }
        }
    }

    return nullptr;
}

statement* parser::find_if_statement(funscope* fscope){
    if(currentmatch(KeywordToken::IF)&&nextmatch(SymbolToken::LEFT_PARENTHESIS)){
        std::vector<ExStmList*>* exstmlists=new std::vector<ExStmList*>();

        auto find_condition_stm_list=[&](expression* ex){
            StmList* stmlist=new StmList();
            if(nextmatch(SymbolToken::LEFT_CURLY_BRACES)){
                next();
                while(!currentmatch(SymbolToken::RIGHT_CURLY_BRACES))
                    add_next_stm_to_stm_list(fscope,stmlist);
                next();
                    
            }else add_next_stm_to_stm_list(fscope,stmlist);
                
            exstmlists->push_back(new std::pair(ex,stmlist));
        };

        auto if_condition=[&](auto& next_condition){
            next();
            auto ex=find_expression();
            if(currentmatch(SymbolToken::RIGHT_PARENTHESIS)){
                find_condition_stm_list(ex);
            }
            next_condition();
        };

        auto else_condition=[&](){
            if(currentmatch(KeywordToken::ELSE)){
                std::wstring True_val=KeywordToken::TRUE.getVal();
                expression* ex=new boolexpression(True_val);
                find_condition_stm_list(ex);
                //next();
            }
        };

        /*auto else_if_condition=[&](){
            while(currentmatch(KeywordToken::ELSE_IF)&&nextmatch(SymbolToken::LEFT_PARENTHESIS)){
                auto empty=[](){};
                if_condition(empty);
            }
            else_condition();
        };*/
        

        if_condition(else_condition);


        auto if_statement=new ifstatement(fscope,exstmlists);
        return if_statement;
    }

    return nullptr;
}

statement* parser::find_return_statement(funscope* fscope){
    if(currentmatch(KeywordToken::RETURN)){
        next();
        //next();
        auto ex=find_expression();
        auto stm=new returnstatement(fscope,ex);
        return stm;
    }
    return nullptr;
}

statement* parser::find_expression_statement(funscope* fscope){
    auto ex=find_expression();
    auto stm=new expressionstatement(fscope,ex);
    //ex->print();
    return stm;
}

statement* parser::find_var_reassign_statement(funscope* fscope){
    if(current.isidentifiertoken()){
        auto varname=current.getVal();
        if(nextmatch(SymbolToken::EQUAL)){
            next();
            auto ex=find_expression();
            auto stm=new varreassignstatement(fscope,varname,ex);
            return stm;
        }
        else if(
            currentmatch(SymbolToken::PLUS)||
            currentmatch(SymbolToken::MINUS)||
            currentmatch(SymbolToken::STAR)||
            currentmatch(SymbolToken::SLASH)||
            currentmatch(SymbolToken::MODULO)||
            currentmatch(SymbolToken::POWER)
        ){
            LexerToken op=current;
            if(nextmatch(SymbolToken::EQUAL)){
                next();
                auto left=new variableaccessexpression(varname);
                auto right=find_expression();
                expression* ex=new binaryexpression(left,op,right);
                auto stm=new varreassignstatement(fscope,varname,ex);
                return stm;
            }
        }
        else{
            currentpos-=2;
            next();
        }
    }
    return nullptr;
}

statement* parser::find_var_val_statement(funscope* fscope){
    auto isvar=currentmatch(KeywordToken::VAR);
    auto isval=currentmatch(KeywordToken::VAL);
    std::wstring name,type=L"";
    expression* ex=nullptr;     
    if(isvar||isval){
        if(next().isidentifiertoken()){
            name=currentval();
            if(nextmatch(SymbolToken::COLON)){
                if(next().isidentifiertoken()){
                    type=currentval();
                    next();
                }
            }
            if(currentmatch(SymbolToken::EQUAL)){
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
    while(currentmatch(SymbolToken::BAR)&&nextmatch(SymbolToken::BAR))
    {   
        LexerToken op=SymbolToken::LOGICAL_OR;
        next();
        right=find_binary_logical_and_expression();
        left=new binaryexpression(left,op,right);
    }
    return left;
    
}

expression* parser::find_binary_logical_and_expression(){
    expression* left=find_binary_equality_expression();
    expression* right;
    while(currentmatch(SymbolToken::AMPERSAND)&&nextmatch(SymbolToken::AMPERSAND))
    {   
        LexerToken op=SymbolToken::LOGICAL_AND;
        next();
        right=find_binary_equality_expression();
        left=new binaryexpression(left,op,right);
    }
    return left;
    
}

expression* parser::find_binary_equality_expression(){
    expression* left=find_binary_comparison_expression();
    expression* right;
    while(currentmatch(SymbolToken::EXCLAMATION_MARK)||currentmatch(SymbolToken::EQUAL))
    {
        LexerToken op=current;
        if(nextmatch(SymbolToken::EQUAL)){
            op=LexerToken(LexerToken::SYMBOL_TOKEN,op.getVal()+L"="); // we don't need if() to make op != or ==
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
        currentmatch(SymbolToken::LEFT_ANGLE_BRACKET)
        ||
        currentmatch(SymbolToken::RIGHT_ANGLE_BRACKET)
    ){
        LexerToken op=current;
        if(nextmatch(SymbolToken::EQUAL)){
            op=LexerToken(LexerToken::SYMBOL_TOKEN,op.getVal()+L"="); // we don't need if() to make op >= or <=
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
        currentmatch(SymbolToken::PLUS)
        ||
        currentmatch(SymbolToken::MINUS)
    ){
        LexerToken op=current;
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
        currentmatch(SymbolToken::STAR)
        ||
        currentmatch(SymbolToken::SLASH)
        ||
        currentmatch(SymbolToken::MODULO)
    ){
        LexerToken op=current;
        next();
        right=find_binary_math_exponent_expression();
        left=new binaryexpression(left,op,right);
    }
    return left;
}

expression* parser::find_binary_math_exponent_expression(){
    expression* left=find_binary_parentheses_expression();
    expression* right;
    while(currentmatch(SymbolToken::POWER)){
        LexerToken op=current;
        next();
        right=find_binary_parentheses_expression();
        left=new binaryexpression(left,op,right);
    }
    return left;
}

expression* parser::find_binary_parentheses_expression(){
    expression* left;
    expression* right;
    if(currentmatch(SymbolToken::LEFT_PARENTHESIS)){
        next();
        left=find_binary_logical_or_expression();
        while(!currentmatch(SymbolToken::RIGHT_PARENTHESIS)){
            LexerToken op=current;
            next();
            right=find_binary_logical_or_expression();
            left=new binaryexpression(left,op,right);
        }
        next();
    }
    else if(current.isstringliteral()){
        auto val=currentval();
        left=new stringexpression(val);
        next();
    }
    else if(currentmatch(KeywordToken::TRUE)||currentmatch(KeywordToken::FALSE)){
        auto val=currentval();
        left=new boolexpression(val);
        next();
    }
    else if(current.isnumberliteral()){
        auto val=currentval();
        left=new numberexpression(val);
        next();
    }
    else if(current.isidentifiertoken()){
        auto name=currentval();
        if(nextmatch(SymbolToken::LEFT_PARENTHESIS)){
            next();
            auto argsex=new std::vector<expression*>();
            while(!currentmatch(SymbolToken::RIGHT_PARENTHESIS)){
                auto argex=find_expression();
                argsex->push_back(argex);
                if(currentmatch(SymbolToken::COMMA)){
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
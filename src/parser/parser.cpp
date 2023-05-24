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

std::wstring parser::currentval(){
    return current.getval();
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
                                auto arg=std::pair<std::wstring,std::wstring>(argname,argtype);
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
                    next();
                    while(!currentmatch(symboltoken::RIGHT_CURLY_BRACES))
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

    auto while_statement=find_while_statement(fscope);
    if(while_statement!=nullptr)
        return while_statement;

    auto expression_statement=find_expression_statement(fscope);
    if(expression_statement!=nullptr)
        return expression_statement;

    return nullptr;
}

statement* parser::find_while_statement(funscope* fscope){
    if(currentmatch(keywordtoken::WHILE)&&nextmatch(symboltoken::LEFT_PARENTHESIS)){
        next();
        auto ex=find_expression();
        if(currentmatch(symboltoken::RIGHT_PARENTHESIS)){
            StmList* stmlist=new StmList();
            if(nextmatch(symboltoken::LEFT_CURLY_BRACES)){
                next();
                while(!currentmatch(symboltoken::RIGHT_CURLY_BRACES))
                    add_next_stm_to_stm_list(fscope,stmlist);
                next();
                    
            }else add_next_stm_to_stm_list(fscope,stmlist);

            auto while_statment=new whilestatement(fscope,ex,stmlist);
            return while_statment;
        }
    }
    return nullptr;
}

statement* parser::find_if_statement(funscope* fscope){
    if(currentmatch(keywordtoken::IF)&&nextmatch(symboltoken::LEFT_PARENTHESIS)){
        std::vector<ExStmList*>* exstmlists=new std::vector<ExStmList*>();

        auto find_condition_stm_list=[&](expression* ex){
            StmList* stmlist=new StmList();
            if(nextmatch(symboltoken::LEFT_CURLY_BRACES)){
                next();
                while(!currentmatch(symboltoken::RIGHT_CURLY_BRACES))
                    add_next_stm_to_stm_list(fscope,stmlist);
                next();
                    
            }else add_next_stm_to_stm_list(fscope,stmlist);
                
            exstmlists->push_back(new std::pair(ex,stmlist));
        };

        auto if_condition=[&](auto& next_condition){
            next();
            auto ex=find_expression();
            if(currentmatch(symboltoken::RIGHT_PARENTHESIS)){
                find_condition_stm_list(ex);
            }
            next_condition();
        };

        auto else_condition=[&](){
            if(currentmatch(keywordtoken::ELSE)){
                std::wstring True_val=keywordtoken::TRUE.getval();
                expression* ex=new boolexpression(True_val);
                find_condition_stm_list(ex);
                //next();
            }
        };

        auto else_if_condition=[&](){
            while(currentmatch(keywordtoken::ELSE_IF)&&nextmatch(symboltoken::LEFT_PARENTHESIS)){
                auto empty=[](){};
                if_condition(empty);
            }
            else_condition();
        };
        

        if_condition(else_condition);


        auto if_statement=new ifstatement(fscope,exstmlists);
        return if_statement;
    }

    return nullptr;
}

statement* parser::find_return_statement(funscope* fscope){
    if(currentmatch(keywordtoken::RETURN)){
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
        auto varname=current.getval();
        if(nextmatch(symboltoken::EQUAL)){
            next();
            auto ex=find_expression();
            auto stm=new varreassignstatement(fscope,varname,ex);
            return stm;
        }
        else if(
            currentmatch(symboltoken::PLUS)||
            currentmatch(symboltoken::MINUS)||
            currentmatch(symboltoken::STAR)||
            currentmatch(symboltoken::SLASH)||
            currentmatch(symboltoken::MODULO)||
            currentmatch(symboltoken::POWER)
        ){
            lexertoken op=current;
            if(nextmatch(symboltoken::EQUAL)){
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
    auto isvar=currentmatch(keywordtoken::VAR);
    auto isval=currentmatch(keywordtoken::VAL);
    std::wstring name,type=L"";
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
    else if(current.isstringliteral()){
        auto val=currentval();
        left=new stringexpression(val);
        next();
    }
    else if(currentmatch(keywordtoken::TRUE)||currentmatch(keywordtoken::FALSE)){
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
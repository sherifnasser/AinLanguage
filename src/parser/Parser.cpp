#include <iostream>
#include <map>
#include "Parser.hpp"
#include "LexerToken.hpp"
#include "KeywordToken.hpp"
#include "SymbolToken.hpp"

#include "GlobalScope.hpp"
#include "FunScope.hpp"
#include "Variable.hpp"
#include "Constant.hpp"

#include "NumberExpression.hpp"
#include "StringExpression.hpp"
#include "BoolExpression.hpp"
#include "BinaryExpression.hpp"
#include "FunCallExpression.hpp"
#include "VariableAccessExpression.hpp"

#include "ExpressionStatement.hpp"
#include "VarReassignStatement.hpp"
#include "VarDeclarationStatement.hpp"
#include "ReturnStatement.hpp"
#include "IfStatement.hpp"
#include "WhileStatement.hpp"
#include "DoWhileStatement.hpp"

#define wcout std::wcout
#define endl std::endl


Parser::Parser(){}

SharedLexerToken Parser::next(){
    currentpos++;
    //wcout<<currentVal()<<endl;
    current=(currentpos<tokens->size())
    ?(*tokens)[currentpos]
    :std::make_shared<LexerToken>(LexerToken(LexerToken::NOT_SET_TOKEN,L""));
    // skip comments
    if(current->getTokenType()!=LexerToken::COMMENT_TOKEN)
        return current;
    return next();
}

bool Parser::currentMatch(LexerToken expected){
    return *current==expected;
}

bool Parser::nextMatch(LexerToken expected){
    next();
    return currentMatch(expected);
}

std::wstring Parser::currentVal(){
    return current->getVal();
}

void Parser::startParse(SharedVector<SharedLexerToken> tokens,SharedGlobalScope globalScope){
    this->tokens=tokens;
    current=next();
    while(!currentMatch(LexerToken::notsettoken)){
        find_functions(globalScope);
        next();
    }
    /*auto ex=find_expression();
    std::wstring tab=L"";
    ex->print(tab);*/
}

void Parser::find_functions(SharedGlobalScope globalScope){
    std::wstring funName;
    std::wstring funType=L"";
    auto args=std::make_shared<std::vector<std::pair<std::wstring,std::wstring>>>();

    if(currentMatch(KeywordToken::FUN)){
        if(next()->isidentifiertoken()){
            funName=currentVal();
            if(nextMatch(SymbolToken::LEFT_PARENTHESIS)){
                /*----------------we have two ways-------------------/*
                1- the next token is left parenthesis and no args for the fun.
                2- there're args in form (arg1:arg1Type, arg2:arg2Type, ...). */
                while(!nextMatch(SymbolToken::RIGHT_PARENTHESIS)){
                    if(current->isidentifiertoken()){
                        auto argname=currentVal();
                        if(nextMatch(SymbolToken::COLON)){
                            if(next()->isidentifiertoken()){
                                auto argType=currentVal();
                                auto arg=std::pair<std::wstring,std::wstring>(argname,argType);
                                args->push_back(arg);
                                // calling next() first multi args without a comma
                                if(nextMatch(SymbolToken::COMMA)){}
                                // the user may right the comma or not at the end
                                else if(currentMatch(SymbolToken::RIGHT_PARENTHESIS))
                                {break;}
                                // else error
                            }
                        }
                    } // else error
                }

                if(nextMatch(SymbolToken::COLON)){
                    if(next()->isidentifiertoken()){
                        funType=currentVal();
                        next();
                    }
                }
                
                auto fScope=std::make_shared<FunScope>(globalScope,funName,funType,args);
                globalScope->addfunction(fScope);

                if(currentMatch(SymbolToken::LEFT_CURLY_BRACES)){
                    next();
                    while(!currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
                        add_next_stm_to_stm_list(fScope,fScope->getStmList());
                }
                // else error
            }
        }
    }
}

void Parser::add_next_stm_to_stm_list(SharedFunScope fScope,SharedVector<SharedIStatement> stmList){
    auto stm=find_next_Statement(fScope);
    if(stm!=nullptr)
        stmList->push_back(stm);
}

SharedIStatement Parser::find_next_Statement(SharedFunScope fScope){
    
    auto var_val_Statement=find_var_val_Statement(fScope);
    if(var_val_Statement!=nullptr)
        return var_val_Statement;
    
    auto var_reassign_Statement=find_var_reassign_Statement(fScope);
    if(var_reassign_Statement!=nullptr)
        return var_reassign_Statement;

    auto return_Statement=find_return_Statement(fScope);
    if(return_Statement!=nullptr)
        return return_Statement;
    
    auto if_Statement=find_if_Statement(fScope);
    if(if_Statement!=nullptr)
        return if_Statement;

    auto do_while_Statement=find_do_while_Statement(fScope);
    if(do_while_Statement!=nullptr)
        return do_while_Statement;

    auto while_Statement=find_while_Statement(fScope);
    if(while_Statement!=nullptr)
        return while_Statement;
        
    auto expression_Statement=find_expression_Statement(fScope);
    if(expression_Statement!=nullptr)
        return expression_Statement;

    return nullptr;
}

SharedIStatement Parser::find_while_Statement(SharedFunScope fScope){
    if(currentMatch(KeywordToken::WHILE)&&nextMatch(SymbolToken::LEFT_PARENTHESIS)){
        next();
        auto ex=find_expression();
        if(currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
            auto stmList=std::make_shared<std::vector<SharedIStatement>>();
            if(nextMatch(SymbolToken::LEFT_CURLY_BRACES)){
                next();
                while(!currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
                    add_next_stm_to_stm_list(fScope,stmList);
                next();
                    
            }else add_next_stm_to_stm_list(fScope,stmList);

            auto while_statment=std::make_shared<WhileStatement>(fScope,ex,stmList);
            return while_statment;
        }
    }
    return nullptr;
}

SharedIStatement Parser::find_do_while_Statement(SharedFunScope fScope){
    if(currentMatch(KeywordToken::DO)){
        auto stmList=std::make_shared<std::vector<SharedIStatement>>();
        if(nextMatch(SymbolToken::LEFT_CURLY_BRACES)){
            next();
            while(!currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
                add_next_stm_to_stm_list(fScope,stmList);
            next();
                    
        }else add_next_stm_to_stm_list(fScope,stmList);

        if(currentMatch(KeywordToken::WHILE)&&nextMatch(SymbolToken::LEFT_PARENTHESIS)){
            next();
            auto ex=find_expression();
            if(currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
                next();
                auto while_statment=std::make_shared<DoWhileStatement>(fScope,ex,stmList);
                return while_statment;
            }
        }
    }

    return nullptr;
}

SharedIStatement Parser::find_if_Statement(SharedFunScope fScope){
    if(currentMatch(KeywordToken::IF)&&nextMatch(SymbolToken::LEFT_PARENTHESIS)){

        auto find_condition_stm_list=[&](SharedVector<SharedIStatement> stmList){
            if(nextMatch(SymbolToken::LEFT_CURLY_BRACES)){
                next();
                while(!currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
                    add_next_stm_to_stm_list(fScope,stmList);
                next();
                    
            }else add_next_stm_to_stm_list(fScope,stmList);
        };

        next();
        auto ifCondition=find_expression();
        SharedVector<SharedIStatement> ifStmList=std::make_shared<std::vector<SharedIStatement>>();;
        SharedVector<SharedIStatement> elseStmList=std::make_shared<std::vector<SharedIStatement>>();;

        if(currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
            find_condition_stm_list(ifStmList);
        }
        if(currentMatch(KeywordToken::ELSE)){
            find_condition_stm_list(elseStmList);
        }
        
        auto if_Statement=std::make_shared<IfStatement>(fScope,ifCondition,ifStmList,elseStmList);
        return if_Statement;
    }

    return nullptr;
}

SharedIStatement Parser::find_return_Statement(SharedFunScope fScope){
    if(currentMatch(KeywordToken::RETURN)){
        next();
        auto ex=find_expression();
        auto stm=std::make_shared<ReturnStatement>(fScope,ex);
        return stm;
    }
    return nullptr;
}

SharedIStatement Parser::find_expression_Statement(SharedFunScope fScope){
    auto ex=find_expression();
    auto stm=std::make_shared<ExpressionStatement>(fScope,ex);
    return stm;
}

SharedIStatement Parser::find_var_reassign_Statement(SharedFunScope fScope){
    if(current->isidentifiertoken()){
        auto varname=current->getVal();
        if(nextMatch(SymbolToken::EQUAL)){
            next();
            auto ex=find_expression();
            auto stm=std::make_shared<VarReassignStatement>(fScope,varname,ex);
            return stm;
        }
        else if(
            currentMatch(SymbolToken::PLUS)||
            currentMatch(SymbolToken::MINUS)||
            currentMatch(SymbolToken::STAR)||
            currentMatch(SymbolToken::SLASH)||
            currentMatch(SymbolToken::MODULO)||
            currentMatch(SymbolToken::POWER)
        ){
            auto op=current;
            if(nextMatch(SymbolToken::EQUAL)){
                next();
                auto left=std::make_shared<VariableAccessExpression>(varname);
                auto right=find_expression();
                auto ex=std::make_shared<BinaryExpression>(left,op,right);
                auto stm=std::make_shared<VarReassignStatement>(fScope,varname,ex);
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

SharedIStatement Parser::find_var_val_Statement(SharedFunScope fScope){
    auto isvar=currentMatch(KeywordToken::VAR);
    auto isval=currentMatch(KeywordToken::VAL);
    std::wstring name,type=L"";
    SharedIExpression ex;     
    if(isvar||isval){
        if(next()->isidentifiertoken()){
            name=currentVal();
            if(nextMatch(SymbolToken::COLON)){
                if(next()->isidentifiertoken()){
                    type=currentVal();
                    next();
                }
            }
            if(currentMatch(SymbolToken::EQUAL)){
                next();
                ex=find_expression();
            }
            SharedVariable var;
            if(isvar){
                var=std::make_shared<Variable>(fScope,name,type);
            }
            else if(isval){
                var=std::make_shared<Constant>(fScope,name,type);
            }
            auto stm=std::make_shared<VarDeclarationStatement>(fScope,var,ex);
            return stm;
        }
    }
    return nullptr;
}

SharedIExpression Parser::find_expression(){
    return find_binary_logical_or_expression();
}

SharedIExpression Parser::find_binary_logical_or_expression(){
    SharedIExpression left=find_binary_logical_and_expression();
    SharedIExpression right;
    while(currentMatch(SymbolToken::LOGICAL_OR))
    {   
        auto op=current;
        next();
        right=find_binary_logical_and_expression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIExpression Parser::find_binary_logical_and_expression(){
    SharedIExpression left=find_binary_equality_expression();
    SharedIExpression right;
    while(currentMatch(SymbolToken::LOGICAL_AND))
    {   
        auto op=current;
        next();
        right=find_binary_equality_expression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIExpression Parser::find_binary_equality_expression(){
    SharedIExpression left=find_binary_comparison_expression();
    SharedIExpression right;
    while(currentMatch(SymbolToken::NOT_EQUAL)||currentMatch(SymbolToken::EQUAL_EQUAL))
    {
        auto op=current;
        next();
        right=find_binary_comparison_expression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIExpression Parser::find_binary_comparison_expression(){
    SharedIExpression left=find_binary_math_plus_minus_expression();
    SharedIExpression right;
    while(
        currentMatch(SymbolToken::LEFT_ANGLE_BRACKET)
        ||
        currentMatch(SymbolToken::RIGHT_ANGLE_BRACKET)
        ||
        currentMatch(SymbolToken::GREATER_EQUAL)
        ||
        currentMatch(SymbolToken::LESS_EQUAL)
    ){
        auto op=current;
        next();
        right=find_binary_math_plus_minus_expression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIExpression Parser::find_binary_math_plus_minus_expression(){
    SharedIExpression left=find_binary_math_star_slash_expression();
    SharedIExpression right;
    while(
        currentMatch(SymbolToken::PLUS)
        ||
        currentMatch(SymbolToken::MINUS)
    ){
        auto op=current;
        next();
        right=find_binary_math_star_slash_expression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIExpression Parser::find_binary_math_star_slash_expression(){
    SharedIExpression left=find_binary_math_exponent_expression();
    SharedIExpression right;
    while(
        currentMatch(SymbolToken::STAR)
        ||
        currentMatch(SymbolToken::SLASH)
        ||
        currentMatch(SymbolToken::MODULO)
    ){
        auto op=current;
        next();
        right=find_binary_math_exponent_expression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
}

SharedIExpression Parser::find_binary_math_exponent_expression(){
    SharedIExpression left=find_binary_parentheses_expression();
    SharedIExpression right;
    while(currentMatch(SymbolToken::POWER)){
        auto op=current;
        next();
        right=find_binary_parentheses_expression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
}

SharedIExpression Parser::find_binary_parentheses_expression(){
    SharedIExpression left;
    SharedIExpression right;
    if(currentMatch(SymbolToken::LEFT_PARENTHESIS)){
        next();
        left=find_binary_logical_or_expression();
        while(!currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
            auto op=current;
            next();
            right=find_binary_logical_or_expression();
            left=std::make_shared<BinaryExpression>(left,op,right);
        }
        next();
    }
    else if(current->isstringliteral()){
        auto val=currentVal();
        left=std::make_shared<StringExpression>(val);
        next();
    }
    else if(currentMatch(KeywordToken::TRUE)||currentMatch(KeywordToken::FALSE)){
        auto val=currentVal();
        left=std::make_shared<BoolExpression>(val);
        next();
    }
    else if(current->isnumberliteral()){
        auto val=currentVal();
        left=std::make_shared<NumberExpression>(val);
        next();
    }
    else if(current->isidentifiertoken()){
        auto name=currentVal();
        if(nextMatch(SymbolToken::LEFT_PARENTHESIS)){
            next();
            auto argsEx=std::make_shared<std::vector<SharedIExpression>>();
            while(!currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
                auto argex=find_expression();
                argsEx->push_back(argex);
                if(currentMatch(SymbolToken::COMMA)){
                    next();
                }
            }
            left=std::make_shared<FunCallExpression>(name,argsEx);
            next();
        }
        else{
            left=std::make_shared<VariableAccessExpression>(name);
        }
    }
    return left;
}
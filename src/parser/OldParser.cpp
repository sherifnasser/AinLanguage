#include <iostream>
#include <map>
#include "LinkedList.hpp"
#include "OldParser.hpp"
#include "LexerToken.hpp"
#include "KeywordToken.hpp"
#include "SharedPtrTypes.hpp"
#include "SymbolToken.hpp"

#include "GlobalScope.hpp"
#include "OldFunScope.hpp"
#include "OldVariable.hpp"
#include "OldConstant.hpp"

#include "NumberExpression.hpp"
#include "StringExpression.hpp"
#include "BoolExpression.hpp"
#include "BinaryExpression.hpp"
#include "FunCallExpression.hpp"
#include "OldVariableAccessExpression.hpp"

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
    currentNode=currentNode->next;
    auto tokenType=currentTokenType();
    // skip those
    if(
        tokenType!=LexerToken::COMMENT_TOKEN
        &&
        tokenType!=LexerToken::SPACE_TOKEN
        &&
        tokenType!=LexerToken::EOL_TOKEN
    )
        return currentToken();
    
    return next();
}

bool Parser::currentMatch(LexerToken expected){
    return *currentToken()==expected;
}

bool Parser::nextMatch(LexerToken expected){
    next();
    return currentMatch(expected);
}

SharedLexerToken Parser::currentToken(){
    return (currentNode)
    ?currentNode->val
    :std::make_shared<LexerToken>(LexerToken::EofToken());
}

std::wstring Parser::currentVal(){
    return currentToken()->getVal();
}

LexerToken::TOKEN_TYPE Parser::currentTokenType(){
    return currentToken()->getTokenType();
}

void Parser::startParse(SharedLinkedList<SharedLexerToken> tokens,SharedGlobalScope globalScope){
    this->tokens=tokens;
    currentNode=tokens->head;
    while(currentTokenType()!=LexerToken::EOF_TOKEN){
        findFunctions(globalScope);
        next();
    }
}

void Parser::findFunctions(SharedGlobalScope globalScope){
    std::wstring funName;
    std::wstring funType=L"";
    auto args=std::make_shared<std::vector<std::pair<std::wstring,std::wstring>>>();

    if(currentMatch(KeywordToken::FUN)){
        if(next()->getTokenType()==LexerToken::IDENTIFIER_TOKEN){
            funName=currentVal();
            if(nextMatch(SymbolToken::LEFT_PARENTHESIS)){
                /*----------------we have two ways-------------------/*
                1- the next token is left parenthesis and no args for the fun.
                2- there're args in form (arg1:arg1Type, arg2:arg2Type, ...). */
                while(!nextMatch(SymbolToken::RIGHT_PARENTHESIS)){
                    if(currentTokenType()==LexerToken::IDENTIFIER_TOKEN){
                        auto argName=currentVal();
                        if(nextMatch(SymbolToken::COLON)){
                            if(next()->getTokenType()==LexerToken::IDENTIFIER_TOKEN){
                                auto argType=currentVal();
                                auto arg=std::pair<std::wstring,std::wstring>(argName,argType);
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
                    if(next()->getTokenType()==LexerToken::IDENTIFIER_TOKEN){
                        funType=currentVal();
                        next();
                    }
                }
                
                auto funScope=std::make_shared<OldFunScope>(globalScope,funName,funType,args);
                globalScope->addfunction(funScope);

                if(currentMatch(SymbolToken::LEFT_CURLY_BRACES)){
                    next();
                    while(!currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
                        addNextStmToStmList(funScope,funScope->getStmList());
                }
                // else error
            }
        }
    }
}

void Parser::addNextStmToStmList(SharedOldFunScope funScope,SharedVector<SharedIOldStatement> stmList){
    auto stm=findNextStatement(funScope);
    if(stm!=nullptr)
        stmList->push_back(stm);
}

SharedIOldStatement Parser::findNextStatement(SharedOldFunScope funScope){
    
    auto var_val_Statement=findVarValStatement(funScope);
    if(var_val_Statement!=nullptr)
        return var_val_Statement;
    
    auto var_reassign_Statement=findVarReassignStatement(funScope);
    if(var_reassign_Statement!=nullptr)
        return var_reassign_Statement;

    auto return_Statement=findReturnStatement(funScope);
    if(return_Statement!=nullptr)
        return return_Statement;
    
    auto if_Statement=findIfStatement(funScope);
    if(if_Statement!=nullptr)
        return if_Statement;

    auto do_while_Statement=findDoWhileStatement(funScope);
    if(do_while_Statement!=nullptr)
        return do_while_Statement;

    auto while_Statement=findWhileStatement(funScope);
    if(while_Statement!=nullptr)
        return while_Statement;
        
    auto expression_Statement=findExpressionStatement(funScope);
    if(expression_Statement!=nullptr)
        return expression_Statement;

    return nullptr;
}

SharedIOldStatement Parser::findWhileStatement(SharedOldFunScope funScope){
    if(currentMatch(KeywordToken::WHILE)&&nextMatch(SymbolToken::LEFT_PARENTHESIS)){
        next();
        auto ex=findExpression();
        if(currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
            auto stmList=std::make_shared<std::vector<SharedIOldStatement>>();
            if(nextMatch(SymbolToken::LEFT_CURLY_BRACES)){
                next();
                while(!currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
                    addNextStmToStmList(funScope,stmList);
                next();
                    
            }else addNextStmToStmList(funScope,stmList);

            auto while_statment=std::make_shared<WhileStatement>(funScope,ex,stmList);
            return while_statment;
        }
    }
    return nullptr;
}

SharedIOldStatement Parser::findDoWhileStatement(SharedOldFunScope funScope){
    if(currentMatch(KeywordToken::DO)){
        auto stmList=std::make_shared<std::vector<SharedIOldStatement>>();
        if(nextMatch(SymbolToken::LEFT_CURLY_BRACES)){
            next();
            while(!currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
                addNextStmToStmList(funScope,stmList);
            next();
                    
        }else addNextStmToStmList(funScope,stmList);

        if(currentMatch(KeywordToken::WHILE)&&nextMatch(SymbolToken::LEFT_PARENTHESIS)){
            next();
            auto ex=findExpression();
            if(currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
                next();
                auto while_statment=std::make_shared<DoWhileStatement>(funScope,ex,stmList);
                return while_statment;
            }
        }
    }

    return nullptr;
}

SharedIOldStatement Parser::findIfStatement(SharedOldFunScope funScope){
    if(currentMatch(KeywordToken::IF)&&nextMatch(SymbolToken::LEFT_PARENTHESIS)){

        auto find_condition_stm_list=[&](SharedVector<SharedIOldStatement> stmList){
            if(nextMatch(SymbolToken::LEFT_CURLY_BRACES)){
                next();
                while(!currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
                    addNextStmToStmList(funScope,stmList);
                next();
                    
            }else addNextStmToStmList(funScope,stmList);
        };

        next();
        auto ifCondition=findExpression();
        SharedVector<SharedIOldStatement> ifStmList=std::make_shared<std::vector<SharedIOldStatement>>();;
        SharedVector<SharedIOldStatement> elseStmList=std::make_shared<std::vector<SharedIOldStatement>>();;

        if(currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
            find_condition_stm_list(ifStmList);
        }
        if(currentMatch(KeywordToken::ELSE)){
            find_condition_stm_list(elseStmList);
        }
        
        auto if_Statement=std::make_shared<IfStatement>(funScope,ifCondition,ifStmList,elseStmList);
        return if_Statement;
    }

    return nullptr;
}

SharedIOldStatement Parser::findReturnStatement(SharedOldFunScope funScope){
    if(currentMatch(KeywordToken::RETURN)){
        next();
        auto ex=findExpression();
        auto stm=std::make_shared<ReturnStatement>(funScope,ex);
        return stm;
    }
    return nullptr;
}

SharedIOldStatement Parser::findExpressionStatement(SharedOldFunScope funScope){
    auto ex=findExpression();
    auto stm=std::make_shared<ExpressionStatement>(funScope,ex);
    return stm;
}

SharedIOldStatement Parser::findVarReassignStatement(SharedOldFunScope funScope){
    if(currentTokenType()==LexerToken::IDENTIFIER_TOKEN){
        auto varname=currentVal();
        auto identifierNode=currentNode; // needed in else block
        if(nextMatch(SymbolToken::EQUAL)){
            next();
            auto ex=findExpression();
            auto stm=std::make_shared<VarReassignStatement>(funScope,varname,ex);
            return stm;
        }
        else if(
            currentMatch(SymbolToken::PLUS_EQUAL)||
            currentMatch(SymbolToken::MINUS_EQUAL)||
            currentMatch(SymbolToken::STAR_EQUAL)||
            currentMatch(SymbolToken::SLASH_EQUAL)||
            currentMatch(SymbolToken::MODULO_EQUAL)||
            currentMatch(SymbolToken::POWER_EQUAL)
        ){
            auto op=std::make_shared<SymbolToken>(currentVal().substr(0,1)); // only the pure operation symbol
            next();
            auto left=std::make_shared<OldVariableAccessExpression>(varname);
            auto right=findExpression();
            auto ex=std::make_shared<BinaryExpression>(left,op,right);
            auto stm=std::make_shared<VarReassignStatement>(funScope,varname,ex);
            return stm;
        }
        else{
            currentNode=identifierNode;
        }
    }
    return nullptr;
}

SharedIOldStatement Parser::findVarValStatement(SharedOldFunScope funScope){
    auto isvar=currentMatch(KeywordToken::VAR);
    auto isval=currentMatch(KeywordToken::VAL);
    std::wstring name,type=L"";
    SharedIOldExpression ex;     
    if(isvar||isval){
        if(next()->getTokenType()==LexerToken::IDENTIFIER_TOKEN){
            name=currentVal();
            if(nextMatch(SymbolToken::COLON)){
                if(next()->getTokenType()==LexerToken::IDENTIFIER_TOKEN){
                    type=currentVal();
                    next();
                }
            }
            if(currentMatch(SymbolToken::EQUAL)){
                next();
                ex=findExpression();
            }
            SharedOldVariable var;
            if(isvar){
                var=std::make_shared<OldVariable>(funScope,name,type);
            }
            else if(isval){
                var=std::make_shared<OldConstant>(funScope,name,type);
            }
            auto stm=std::make_shared<VarDeclarationStatement>(funScope,var,ex);
            return stm;
        }
    }
    return nullptr;
}

SharedIOldExpression Parser::findExpression(){
    return findBinaryLogicalOrExpression();
}

SharedIOldExpression Parser::findBinaryLogicalOrExpression(){
    SharedIOldExpression left=findBinaryLogicalAndExpression();
    SharedIOldExpression right;
    while(currentMatch(SymbolToken::LOGICAL_OR))
    {   
        auto op=currentToken();
        next();
        right=findBinaryLogicalAndExpression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIOldExpression Parser::findBinaryLogicalAndExpression(){
    SharedIOldExpression left=findBinaryEqualityExpression();
    SharedIOldExpression right;
    while(currentMatch(SymbolToken::LOGICAL_AND))
    {   
        auto op=currentToken();
        next();
        right=findBinaryEqualityExpression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIOldExpression Parser::findBinaryEqualityExpression(){
    SharedIOldExpression left=findBinaryComparisonExpression();
    SharedIOldExpression right;
    while(currentMatch(SymbolToken::NOT_EQUAL)||currentMatch(SymbolToken::EQUAL_EQUAL))
    {
        auto op=currentToken();
        next();
        right=findBinaryComparisonExpression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIOldExpression Parser::findBinaryComparisonExpression(){
    SharedIOldExpression left=findBinaryPlusMinusExpression();
    SharedIOldExpression right;
    while(
        currentMatch(SymbolToken::LEFT_ANGLE_BRACKET)
        ||
        currentMatch(SymbolToken::RIGHT_ANGLE_BRACKET)
        ||
        currentMatch(SymbolToken::GREATER_EQUAL)
        ||
        currentMatch(SymbolToken::LESS_EQUAL)
    ){
        auto op=currentToken();
        next();
        right=findBinaryPlusMinusExpression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIOldExpression Parser::findBinaryPlusMinusExpression(){
    SharedIOldExpression left=findBinaryStarSlashExpression();
    SharedIOldExpression right;
    while(
        currentMatch(SymbolToken::PLUS)
        ||
        currentMatch(SymbolToken::MINUS)
    ){
        auto op=currentToken();
        next();
        right=findBinaryStarSlashExpression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
    
}

SharedIOldExpression Parser::findBinaryStarSlashExpression(){
    SharedIOldExpression left=findBinaryExponentExpression();
    SharedIOldExpression right;
    while(
        currentMatch(SymbolToken::STAR)
        ||
        currentMatch(SymbolToken::SLASH)
        ||
        currentMatch(SymbolToken::MODULO)
    ){
        auto op=currentToken();
        next();
        right=findBinaryExponentExpression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
}

SharedIOldExpression Parser::findBinaryExponentExpression(){
    SharedIOldExpression left=findBinaryParenthesesExpression();
    SharedIOldExpression right;
    while(currentMatch(SymbolToken::POWER)){
        auto op=currentToken();
        next();
        right=findBinaryParenthesesExpression();
        left=std::make_shared<BinaryExpression>(left,op,right);
    }
    return left;
}

SharedIOldExpression Parser::findBinaryParenthesesExpression(){
    SharedIOldExpression left;
    SharedIOldExpression right;
    if(currentMatch(SymbolToken::LEFT_PARENTHESIS)){
        next();
        left=findBinaryLogicalOrExpression();
        while(!currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
            auto op=currentToken();
            next();
            right=findBinaryLogicalOrExpression();
            left=std::make_shared<BinaryExpression>(left,op,right);
        }
        next();
    }
    else if(LexerToken::isStringLiteral(currentToken())){
        auto val=currentVal();
        left=std::make_shared<StringExpression>(val);
        next();
    }
    else if(currentMatch(KeywordToken::TRUE)||currentMatch(KeywordToken::FALSE)){
        auto val=currentVal();
        left=std::make_shared<BoolExpression>(val);
        next();
    }
    else if(LexerToken::isNumberLiteral(currentToken())){
        auto val=currentVal();
        left=std::make_shared<NumberExpression>(val);
        next();
    }
    else if(currentTokenType()==LexerToken::IDENTIFIER_TOKEN){
        auto name=currentVal();
        if(nextMatch(SymbolToken::LEFT_PARENTHESIS)){
            next();
            auto argsEx=std::make_shared<std::vector<SharedIOldExpression>>();
            while(!currentMatch(SymbolToken::RIGHT_PARENTHESIS)){
                auto argex=findExpression();
                argsEx->push_back(argex);
                if(currentMatch(SymbolToken::COMMA)){
                    next();
                }
            }
            left=std::make_shared<FunCallExpression>(name,argsEx);
            next();
        }
        else{
            left=std::make_shared<OldVariableAccessExpression>(name);
        }
    }
    return left;
}
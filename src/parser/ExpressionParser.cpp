#include "ExpressionParser.hpp"
#include "AssignStatement.hpp"
#include "BoolValue.hpp"
#include "CharValue.hpp"
#include "DoubleValue.hpp"
#include "FloatValue.hpp"
#include "FunInvokeExpression.hpp"
#include "IExpression.hpp"
#include "IntValue.hpp"
#include "KeywordToken.hpp"
#include "LexerToken.hpp"
#include "LiteralExpression.hpp"
#include "LiteralToken.hpp"
#include "LogicalExpression.hpp"
#include "LongValue.hpp"
#include "NewObjectExpression.hpp"
#include "NonStaticFunInvokeExpression.hpp"
#include "NonStaticVarAccessExpression.hpp"
#include "NumberToken.hpp"
#include "OnlyVariablesAreAssignableException.hpp"
#include "OperatorFunInvokeExpression.hpp"
#include "OperatorFunctions.hpp"
#include "SharedPtrTypes.hpp"
#include "StmListScope.hpp"
#include "StringValue.hpp"
#include "SymbolToken.hpp"
#include "Type.hpp"
#include "UIntValue.hpp"
#include "ULongValue.hpp"
#include "UnitExpression.hpp"
#include "VarAccessExpression.hpp"
#include <algorithm>
#include <memory>
#include <map>
#include <string>
#include <vector>

ExpressionParser::ExpressionParser(
    SharedTokensIterator iterator,
    SharedBaseScope scope,
    TypeParserProvider typeParserProvider
):BaseParser(iterator,scope),typeParserProvider(typeParserProvider){}

SharedIExpression ExpressionParser::parse(){
    return parseBinaryOperatorExpression();
}

SharedIExpression ExpressionParser::parseBinaryOperatorExpression(int precedence){
    if(precedence==0)
        return parsePrimaryExpression();
    
    auto left=parseBinaryOperatorExpression(precedence-1);

    while(currentMatchByPrecedence(precedence)){
        int lineNumber=iterator->lineNumber;

        auto op=iterator->currentToken();

        iterator->next();
        
        auto right=parseBinaryOperatorExpression(precedence-1);

        if(*op==SymbolToken::LOGICAL_OR){
            left=std::make_shared<LogicalExpression>(
                lineNumber,LogicalExpression::Operation::OR,left,right
            );
            continue;
        }

        if(*op==SymbolToken::LOGICAL_AND){
            left=std::make_shared<LogicalExpression>(
                lineNumber,LogicalExpression::Operation::AND,left,right
            );
            continue;
        }

        auto args=std::make_shared<std::vector<SharedIExpression>>(std::vector({right}));

        left=std::make_shared<OperatorFunInvokeExpression>(
            lineNumber,
            getBinOpFromToken(*op),
            args,
            left
        );
        
    }

    return left;
}

SharedIExpression ExpressionParser::parsePrimaryExpression(){
    
    if(auto unaryOpEx=parseUnaryOperatorExpression())
        return unaryOpEx;
    
    SharedIExpression primary;

    if(auto parenthesesEx=parseParenthesesExpression())
        primary=parenthesesEx;

    else if(auto literalEx=parseLiteralExpression())
        primary=literalEx;

    else if(auto idEx=parseIdentifierExpression())
        primary=idEx;

    else if(auto newObjEx=parseNewObjectExpression())
        primary=newObjEx;

    else
        return nullptr;

    return parseNonStaticAccessExpression(primary);
    
}

SharedIExpression ExpressionParser::parseUnaryOperatorExpression(){

    OperatorFunInvokeExpression::Operator unaryOp;

    if(iterator->currentMatch(SymbolToken::PLUS))
        unaryOp=OperatorFunInvokeExpression::Operator::UNARY_PLUS;

    else if(iterator->currentMatch(SymbolToken::MINUS))
        unaryOp=OperatorFunInvokeExpression::Operator::UNARY_MINUS;

    else if(iterator->currentMatch(SymbolToken::EXCLAMATION_MARK))
        unaryOp=OperatorFunInvokeExpression::Operator::LOGICAL_NOT;

    else if(iterator->currentMatch(SymbolToken::PLUS_PLUS))
        unaryOp=OperatorFunInvokeExpression::Operator::PRE_INC;

    else if(iterator->currentMatch(SymbolToken::MINUS_MINUS))
        unaryOp=OperatorFunInvokeExpression::Operator::PRE_DEC;

    else
        return nullptr;
    
    auto lineNumber=iterator->lineNumber;

    iterator->next();

    auto primary=parsePrimaryExpression();

    if(
        (
            unaryOp==OperatorFunInvokeExpression::Operator::PRE_INC
            ||
            unaryOp==OperatorFunInvokeExpression::Operator::PRE_DEC
        )
        &&
        !IExpression::isAssignableExpression(primary)
    )
        throw OnlyVariablesAreAssignableException(lineNumber);

    auto args=std::make_shared<std::vector<SharedIExpression>>(
        std::vector<SharedIExpression>{}
    );
    
    return std::make_shared<OperatorFunInvokeExpression>(
        lineNumber,
        unaryOp,
        args,
        primary
    );
    
}

SharedIExpression ExpressionParser::parseParenthesesExpression(){
    
    if(!iterator->currentMatch(SymbolToken::LEFT_PARENTHESIS))
        return nullptr;
    
    iterator->next();

    auto ex=parseBinaryOperatorExpression();

    expectSymbol(SymbolToken::RIGHT_PARENTHESIS);

    iterator->next();

    return ex;
}

SharedIExpression ExpressionParser::parseLiteralExpression(){

    int lineNumber=iterator->lineNumber;

    if(iterator->currentMatch(KeywordToken::TRUE)){
        iterator->next();
        auto value=std::make_shared<BoolValue>(true);
        return std::make_shared<LiteralExpression>(lineNumber,value);
    }

    if(iterator->currentMatch(KeywordToken::FALSE)){
        iterator->next();
        auto value=std::make_shared<BoolValue>(false);
        return std::make_shared<LiteralExpression>(lineNumber,value);
    }
        
    
    auto literal=std::dynamic_pointer_cast<LiteralToken>(iterator->currentToken());
    
    if(!literal)
        return nullptr;
    
    SharedIValue value;

    switch(literal->getLiteralType()){

        case LiteralToken::STRING:{
            auto val=literal->getVal();
            value=std::make_shared<StringValue>(
                val.substr(1,val.size()-2) // remove quotes
            );
            break;
        }

        case LiteralToken::CHAR:{
            value=std::make_shared<CharValue>(
                literal->getVal().at(1) // remove quotes
            );
            break;
        }

        case LiteralToken::NUMBER:{
            auto numType=std::dynamic_pointer_cast<NumberToken>(literal)->getNumberType();
            value=parseNumberValue(numType,literal->getVal());
            break;
        }

        default:{}
    }

    iterator->next();

    return std::make_shared<LiteralExpression>(lineNumber,value);
}

SharedIExpression ExpressionParser::parseIdentifierExpression(){
    
    if(iterator->currentTokenType()!=LexerToken::IDENTIFIER_TOKEN)
        return nullptr;
    
    auto lineNumber=iterator->lineNumber;
    
    auto id=iterator->currentVal();

    if(iterator->nextMatch(SymbolToken::LEFT_PARENTHESIS)){
        auto args=expectFunArgs();
        
        auto funEx=std::make_shared<FunInvokeExpression>(
            lineNumber,
            id,
            args
        );
        return funEx;
    }

    SharedVariable var;

    auto stmListScope=std::dynamic_pointer_cast<StmListScope>(scope);

    if(stmListScope)
        var=stmListScope->getLocalByName(id);
    
    auto varEx=std::make_shared<VarAccessExpression>(lineNumber,id,var);

    return varEx;
    
}

SharedIExpression ExpressionParser::parseNewObjectExpression(){

    if(!iterator->currentMatch(KeywordToken::NEW))
        return nullptr;
    
    int lineNumber=iterator->lineNumber;

    iterator->next();

    auto type=typeParserProvider(iterator,scope)->parse();

    auto args=expectFunArgs();

    auto newObjEx=std::make_shared<NewObjectExpression>(
        lineNumber,
        type,
        args
    );

    return newObjEx;
}

SharedIExpression ExpressionParser::parseNonStaticAccessExpression(SharedIExpression inside){

    auto ex=parsePostIncDecExpression(inside);

    if(!iterator->currentMatch(SymbolToken::DOT))
        return ex;
    
    iterator->next();
    
    int lineNumber=iterator->lineNumber;

    // TODO: right might be inner class instantiation

    auto id=expectIdentifier();
    
    if(iterator->nextMatch(SymbolToken::LEFT_PARENTHESIS))
        ex=std::make_shared<NonStaticFunInvokeExpression>(
            lineNumber,
            id,
            expectFunArgs(),
            inside
        );
    else
        ex=std::make_shared<NonStaticVarAccessExpression>(
            lineNumber,
            id,
            inside
        );
    
    return parseNonStaticAccessExpression(ex);
}

SharedIExpression ExpressionParser::parsePostIncDecExpression(SharedIExpression inside){


    OperatorFunInvokeExpression::Operator unaryOp;

    if(iterator->currentMatch(SymbolToken::PLUS_PLUS))
        unaryOp=OperatorFunInvokeExpression::Operator::POST_INC;

    else if(iterator->currentMatch(SymbolToken::MINUS_MINUS))
        unaryOp=OperatorFunInvokeExpression::Operator::POST_DEC;

    else
        return inside;

    auto lineNumber=iterator->lineNumber;

    if(!IExpression::isAssignableExpression(inside))
        throw OnlyVariablesAreAssignableException(lineNumber);

    iterator->next();

    auto args=std::make_shared<std::vector<SharedIExpression>>(
        std::vector<SharedIExpression>{}
    );
    
    return std::make_shared<OperatorFunInvokeExpression>(
        lineNumber,
        unaryOp,
        args,
        inside
    );
    
}

bool ExpressionParser::currentMatchByPrecedence(int precedence){
    switch(precedence){
        case LOWEST_PRECEDENCE:
            return iterator->currentMatch(SymbolToken::LOGICAL_OR);
        case LOWEST_PRECEDENCE-1:
            return iterator->currentMatch(SymbolToken::LOGICAL_AND);
        case LOWEST_PRECEDENCE-2:
            return
                iterator->currentMatch(SymbolToken::EQUAL_EQUAL)
                ||
                iterator->currentMatch(SymbolToken::NOT_EQUAL)
            ;
        case LOWEST_PRECEDENCE-3:
            return
                iterator->currentMatch(SymbolToken::GREATER_EQUAL)
                ||
                iterator->currentMatch(SymbolToken::LESS_EQUAL)
                ||
                iterator->currentMatch(SymbolToken::LEFT_ANGLE_BRACKET)
                ||
                iterator->currentMatch(SymbolToken::RIGHT_ANGLE_BRACKET)
            ;
        case LOWEST_PRECEDENCE-4:
            return
                iterator->currentMatch(SymbolToken::PLUS)
                ||
                iterator->currentMatch(SymbolToken::MINUS)
            ;
        case LOWEST_PRECEDENCE-5:
            return
                iterator->currentMatch(SymbolToken::STAR)
                ||
                iterator->currentMatch(SymbolToken::SLASH)
                ||
                iterator->currentMatch(SymbolToken::MODULO)
            ;
        case LOWEST_PRECEDENCE-6:
            return iterator->currentMatch(SymbolToken::POWER);
    }
    return false;
}

OperatorFunInvokeExpression::Operator ExpressionParser::getBinOpFromToken(LexerToken op){
        
    if(op==SymbolToken::PLUS)
        return OperatorFunInvokeExpression::Operator::PLUS;
    if(op==SymbolToken::MINUS)
        return OperatorFunInvokeExpression::Operator::MINUS;
    if(op==SymbolToken::STAR)
        return OperatorFunInvokeExpression::Operator::TIMES;
    if(op==SymbolToken::SLASH)
        return OperatorFunInvokeExpression::Operator::DIV;
    if(op==SymbolToken::MODULO)
        return OperatorFunInvokeExpression::Operator::MOD;
    if(op==SymbolToken::POWER)
        return OperatorFunInvokeExpression::Operator::POW;
    if(op==SymbolToken::EQUAL_EQUAL)
        return OperatorFunInvokeExpression::Operator::EQUAL_EQUAL;
    if(op==SymbolToken::NOT_EQUAL)
        return OperatorFunInvokeExpression::Operator::NOT_EQUAL;
    if(op==SymbolToken::LEFT_ANGLE_BRACKET)
        return OperatorFunInvokeExpression::Operator::LESS;
    if(op==SymbolToken::LESS_EQUAL)
        return OperatorFunInvokeExpression::Operator::LESS_EQUAL;
    if(op==SymbolToken::RIGHT_ANGLE_BRACKET)
        return OperatorFunInvokeExpression::Operator::GREATER;
    if(op==SymbolToken::GREATER_EQUAL)
        return OperatorFunInvokeExpression::Operator::GREATER_EQUAL;
    
}

SharedIValue ExpressionParser::parseNumberValue(NumberToken::NUMBER_TYPE numType,std::wstring value) {
    switch(numType){
        case NumberToken::INT:
            return std::make_shared<IntValue>(
                std::stoi(value)
            );

        case NumberToken::UNSIGNED_INT:
            return std::make_shared<UIntValue>(
                std::stoul(value)
            );

        case NumberToken::LONG:
            return std::make_shared<LongValue>(
                std::stoll(value)
            );

        case NumberToken::UNSIGNED_LONG:
            return std::make_shared<ULongValue>(
                std::stoull(value)
            );

        case NumberToken::DOUBLE:
            return std::make_shared<DoubleValue>(
                std::stold(value)
            );

        case NumberToken::FLOAT:
            return std::make_shared<FloatValue>(
                std::stof(value)
            );
    }

    // To stop compiler warnings
    return nullptr;
}

SharedVector<SharedIExpression> ExpressionParser::expectFunArgs(){

    expectSymbol(SymbolToken::LEFT_PARENTHESIS);

    SharedVector<SharedIExpression> args=std::make_shared<std::vector<SharedIExpression>>();

    do{

        if(iterator->nextMatch(SymbolToken::RIGHT_PARENTHESIS))
            break;

        auto arg=parse();

        args->push_back(arg);

    }while(iterator->currentMatch(SymbolToken::COMMA));

    expectSymbol(SymbolToken::RIGHT_PARENTHESIS);

    iterator->next();

    return args;
}
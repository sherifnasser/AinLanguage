#include "ExpressionParser.hpp"
#include "FunInvokeExpression.hpp"
#include "KeywordToken.hpp"
#include "LexerToken.hpp"
#include "LiteralExpression.hpp"
#include "LiteralToken.hpp"
#include "NewObjectExpression.hpp"
#include "NonStaticFunInvokeExpression.hpp"
#include "NonStaticVarAccessExpression.hpp"
#include "NumberToken.hpp"
#include "OperatorFunInvokeExpression.hpp"
#include "PrimitiveValue.hpp"
#include "SharedPtrTypes.hpp"
#include "StmListScope.hpp"
#include "StringValue.hpp"
#include "SymbolToken.hpp"
#include "Type.hpp"
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
    if(precedence==1)
        return parsePrimaryExpression();
    
    auto left=parseBinaryOperatorExpression(precedence-1);

    while(currentMatchByPrecedence(precedence)){
        int lineNumber=iterator->lineNumber;
        auto op=iterator->currentToken();
        auto right=parseBinaryOperatorExpression(precedence-1);
        auto args=std::make_shared<std::vector<SharedIExpression>>(std::vector({right}));
        left=std::make_shared<OperatorFunInvokeExpression>(
            lineNumber,
            op,
            args,
            left
        );
    }

    return left;
}


SharedIExpression ExpressionParser::parsePrimaryExpression(){
    
    SharedIExpression primary;
    if(auto parenthesesEx=parseParenthesesExpression())
        primary=parenthesesEx;
    else if(auto literalEx=parseLiteralExpression())
        primary=literalEx;
    else if(auto idEx=parseIdentifierExpression())
        primary=idEx;
    else if(auto newObjEx=parseNewObjectExpression())
        primary=newObjEx;

    if(!iterator->currentMatch(SymbolToken::DOT))
        return primary;
    
    iterator->next();
    return parseNonStaticAccessExpression(primary);
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
    
    auto literal=std::dynamic_pointer_cast<LiteralToken>(iterator->currentToken());
    if(!literal)
        return nullptr;

    int lineNumber=iterator->lineNumber;
    
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
            value=std::make_shared<PrimitiveValue<wchar_t>>(
                Type::CHAR,
                literal->getVal().at(1) // remove quotes
            );
            break;
        }

        case LiteralToken::NUMBER:{
            auto numType=std::dynamic_pointer_cast<NumberToken>(literal)->getNumberType();
            value=parseNumberValue(numType,literal->getVal());
            break;
        }

        // FIXME bool are keyword tokens
        case LiteralToken::BOOL: {break;}
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

SharedIExpression ExpressionParser::parseNonStaticAccessExpression(SharedIExpression inside) {
    
    int lineNumber=iterator->lineNumber;

    // TODO: right might be inner class instantiation

    auto id=expectIdentifier();
    
    if(!iterator->nextMatch(SymbolToken::LEFT_PARENTHESIS))
        return std::make_shared<NonStaticVarAccessExpression>(
            lineNumber,
            id,
            inside
        );
    
    auto args=expectFunArgs();

    return std::make_shared<NonStaticFunInvokeExpression>(
        lineNumber,
        id,
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

SharedIValue ExpressionParser::parseNumberValue(NumberToken::NUMBER_TYPE numType,std::wstring value) {
    switch(numType){
        case NumberToken::INT:
            return std::make_shared<PrimitiveValue<int>>(
                Type::INT,
                std::stoi(value)
            );

        case NumberToken::UNSIGNED_INT:
            return std::make_shared<PrimitiveValue<unsigned int>>(
                Type::UINT,
                std::stoul(value)
            );

        case NumberToken::LONG:
            return std::make_shared<PrimitiveValue<long long>>(
                Type::LONG,
                std::stoll(value)
            );

        case NumberToken::UNSIGNED_LONG:
            return std::make_shared<PrimitiveValue<unsigned long long>>(
                Type::ULONG,
                std::stoull(value)
            );

        case NumberToken::DOUBLE:
            return std::make_shared<PrimitiveValue<double>>(
                Type::DOUBLE,
                std::stold(value)
            );

        case NumberToken::FLOAT:
            return std::make_shared<PrimitiveValue<float>>(
                Type::FLOAT,
                std::stof(value)
            );
    }
}

SharedVector<SharedIExpression> ExpressionParser::expectFunArgs(){

    expectSymbol(SymbolToken::LEFT_PARENTHESIS);

    SharedVector<SharedIExpression> args;

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
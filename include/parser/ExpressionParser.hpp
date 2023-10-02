#pragma once
#include "BaseParser.hpp"
#include "NumberToken.hpp"
#include "OperatorFunInvokeExpression.hpp"
#include "SharedPtrTypes.hpp"
#include "ParserProvidersAliases.hpp"
#include "SymbolToken.hpp"
#include <string>
class ExpressionParser:public BaseParser<SharedIExpression>{
    public:
        ExpressionParser(
            SharedTokensIterator iterator,
            SharedBaseScope scope,
            TypeParserProvider typeParserProvider
        );

        SharedIExpression parse()override;
    private:
        static const int LOWEST_PRECEDENCE=11;

        TypeParserProvider typeParserProvider;

        SharedIExpression parseBinaryOperatorExpression(int precedence=LOWEST_PRECEDENCE);

        SharedIExpression parsePrimaryExpression();

        SharedIExpression parseUnaryOperatorExpression();

        SharedIExpression parseParenthesesExpression();

        SharedIExpression parseLiteralExpression();

        SharedIExpression parseIdentifierExpression();

        SharedIExpression parseNewExpression();

        SharedIExpression parseNonStaticAccessExpression(SharedIExpression inside);

        SharedIExpression parsePostIncDecExpression(SharedIExpression inside);
        
        bool currentMatchByPrecedence(int precedence);

        OperatorFunInvokeExpression::Operator getBinOpFromToken(LexerToken op);

        SharedIValue parseNumberValue(NumberToken::NUMBER_TYPE numType,std::wstring value);

        SharedVector<SharedIExpression> expectFunArgs();
        
};
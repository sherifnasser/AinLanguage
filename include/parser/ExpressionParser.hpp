#pragma once
#include "BaseParser.hpp"
#include "NumberToken.hpp"
#include "SharedPtrTypes.hpp"
#include "ParserProvidersAliases.hpp"
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
        static const int LOWEST_PRECEDENCE=7;

        TypeParserProvider typeParserProvider;

        SharedIExpression parseBinaryOperatorExpression(int precedence=LOWEST_PRECEDENCE);

        SharedIExpression parsePrimaryExpression();

        SharedIExpression parseParenthesesExpression();

        SharedIExpression parseLiteralExpression();

        SharedIExpression parseIdentifierExpression();

        SharedIExpression parseNewObjectExpression();

        SharedIExpression parseNonStaticAccessExpression(SharedIExpression inside);
        
        bool currentMatchByPrecedence(int precedence);

        SharedIValue parseNumberValue(NumberToken::NUMBER_TYPE numType,std::wstring value);

        SharedVector<SharedIExpression> expectFunArgs();
};
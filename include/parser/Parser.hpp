#pragma once
#include "IParser.hpp"
#include "LexerToken.hpp"
class Parser:public IParser
{
private:
    SharedLinkedList<SharedLexerToken> tokens;
    SharedLinkedListNode<SharedLexerToken> currentNode;
    SharedLexerToken next();
    bool currentMatch(LexerToken expected);
    bool nextMatch(LexerToken expected);
    SharedLexerToken currentToken();
    std::wstring currentVal();
    LexerToken::TOKEN_TYPE currentTokenType();
    void findFunctions(SharedGlobalScope globalScope);
    SharedIStatement findNextStatement(SharedFunScope funScope);
    SharedIStatement findVarValStatement(SharedFunScope funScope);
    SharedIStatement findVarReassignStatement(SharedFunScope funScope);
    SharedIStatement findReturnStatement(SharedFunScope funScope);
    SharedIStatement findExpressionStatement(SharedFunScope funScope);
    SharedIStatement findIfStatement(SharedFunScope funScope);
    SharedIStatement findWhileStatement(SharedFunScope funScope);
    SharedIStatement findDoWhileStatement(SharedFunScope funScope);
    SharedIExpression findExpression();
    SharedIExpression findBinaryLogicalOrExpression();
    SharedIExpression findBinaryLogicalAndExpression();
    SharedIExpression findBinaryEqualityExpression();
    SharedIExpression findBinaryComparisonExpression();
    SharedIExpression findBinaryPlusMinusExpression();
    SharedIExpression findBinaryStarSlashExpression();
    SharedIExpression findBinaryExponentExpression();
    SharedIExpression findBinaryParenthesesExpression();
    void addNextStmToStmList(SharedFunScope fScope,SharedVector<SharedIStatement> stmList);

public:
    Parser();
    void startParse(SharedLinkedList<SharedLexerToken> tokens,SharedGlobalScope GlobalScope)override;
};
#pragma once
#include "OldIParser.hpp"
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
    SharedIStatement findNextStatement(SharedOldFunScope funScope);
    SharedIStatement findVarValStatement(SharedOldFunScope funScope);
    SharedIStatement findVarReassignStatement(SharedOldFunScope funScope);
    SharedIStatement findReturnStatement(SharedOldFunScope funScope);
    SharedIStatement findExpressionStatement(SharedOldFunScope funScope);
    SharedIStatement findIfStatement(SharedOldFunScope funScope);
    SharedIStatement findWhileStatement(SharedOldFunScope funScope);
    SharedIStatement findDoWhileStatement(SharedOldFunScope funScope);
    SharedIExpression findExpression();
    SharedIExpression findBinaryLogicalOrExpression();
    SharedIExpression findBinaryLogicalAndExpression();
    SharedIExpression findBinaryEqualityExpression();
    SharedIExpression findBinaryComparisonExpression();
    SharedIExpression findBinaryPlusMinusExpression();
    SharedIExpression findBinaryStarSlashExpression();
    SharedIExpression findBinaryExponentExpression();
    SharedIExpression findBinaryParenthesesExpression();
    void addNextStmToStmList(SharedOldFunScope fScope,SharedVector<SharedIStatement> stmList);

public:
    Parser();
    void startParse(SharedLinkedList<SharedLexerToken> tokens,SharedGlobalScope GlobalScope)override;
};
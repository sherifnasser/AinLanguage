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
    SharedIOldStatement findNextStatement(SharedOldFunScope funScope);
    SharedIOldStatement findVarValStatement(SharedOldFunScope funScope);
    SharedIOldStatement findVarReassignStatement(SharedOldFunScope funScope);
    SharedIOldStatement findReturnStatement(SharedOldFunScope funScope);
    SharedIOldStatement findExpressionStatement(SharedOldFunScope funScope);
    SharedIOldStatement findIfStatement(SharedOldFunScope funScope);
    SharedIOldStatement findWhileStatement(SharedOldFunScope funScope);
    SharedIOldStatement findDoWhileStatement(SharedOldFunScope funScope);
    SharedIOldExpression findExpression();
    SharedIOldExpression findBinaryLogicalOrExpression();
    SharedIOldExpression findBinaryLogicalAndExpression();
    SharedIOldExpression findBinaryEqualityExpression();
    SharedIOldExpression findBinaryComparisonExpression();
    SharedIOldExpression findBinaryPlusMinusExpression();
    SharedIOldExpression findBinaryStarSlashExpression();
    SharedIOldExpression findBinaryExponentExpression();
    SharedIOldExpression findBinaryParenthesesExpression();
    void addNextStmToStmList(SharedOldFunScope fScope,SharedVector<SharedIOldStatement> stmList);

public:
    Parser();
    void startParse(SharedLinkedList<SharedLexerToken> tokens,SharedGlobalScope GlobalScope)override;
};
#pragma once
#include "IParser.hpp"
class Parser:public IParser
{
private:
    SharedVector<SharedLexerToken> tokens;
    SharedLexerToken current;
    int currentPos=-1;
    SharedLexerToken next();
    bool currentMatch(LexerToken expected);
    bool nextMatch(LexerToken expected);
    std::wstring currentVal();
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
    void startParse(SharedVector<SharedLexerToken> tokens,SharedGlobalScope GlobalScope)override;
};
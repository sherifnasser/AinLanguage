#pragma once
#include "IParser.hpp"
class Parser:public IParser
{
private:
    SharedVector<SharedLexerToken> tokens;
    SharedLexerToken current;
    int currentpos=-1;
    SharedLexerToken next();
    bool currentMatch(LexerToken expected);
    bool nextMatch(LexerToken expected);
    std::wstring currentVal();
    void find_functions(SharedGlobalScope globalScope);
    SharedIStatement find_next_Statement(SharedFunScope FunScope);
    SharedIStatement find_var_val_Statement(SharedFunScope FunScope);
    SharedIStatement find_var_reassign_Statement(SharedFunScope FunScope);
    SharedIStatement find_return_Statement(SharedFunScope FunScope);
    SharedIStatement find_expression_Statement(SharedFunScope FunScope);
    SharedIStatement find_if_Statement(SharedFunScope FunScope);
    SharedIStatement find_while_Statement(SharedFunScope FunScope);
    SharedIStatement find_do_while_Statement(SharedFunScope FunScope);
    SharedIExpression find_expression();
    SharedIExpression find_binary_logical_or_expression();
    SharedIExpression find_binary_logical_and_expression();
    SharedIExpression find_binary_equality_expression();
    SharedIExpression find_binary_comparison_expression();
    SharedIExpression find_binary_math_plus_minus_expression();
    SharedIExpression find_binary_math_star_slash_expression();
    SharedIExpression find_binary_math_exponent_expression();
    SharedIExpression find_binary_parentheses_expression();
    void add_next_stm_to_stm_list(SharedFunScope fScope,SharedVector<SharedIStatement> stmList);

public:
    Parser();
    void startParse(SharedVector<SharedLexerToken> tokens,SharedGlobalScope GlobalScope)override;
};
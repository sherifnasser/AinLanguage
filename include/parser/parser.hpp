#pragma once
#include <iostream>
#include <vector>
#include "lexertoken.hpp"
#include "globalscope.hpp"
#include "expression.hpp"
class parser
{
private:
    std::vector<lexertoken>* tokens;
    lexertoken current;
    int currentpos=-1;
    lexertoken next();
    bool currentmatch(lexertoken expected);
    bool nextmatch(lexertoken expected);
    wstring currentval();
    void find_functions(globalscope &globalscope);
    void find_next_statement(funscope* funscope);
    statement* find_var_val_statement(funscope* funscope);
    expression* find_expression();
    expression* find_binary_logical_or_expression();
    expression* find_binary_logical_and_expression();
    expression* find_binary_equality_expression();
    expression* find_binary_comparison_expression();
    expression* find_binary_math_plus_minus_expression();
    expression* find_binary_math_star_slash_expression();
    expression* find_binary_math_exponent_expression();
    expression* find_binary_parentheses_expression();

public:
    parser(std::vector<lexertoken>* tokens);
    void startparse(globalscope globalscope);
};
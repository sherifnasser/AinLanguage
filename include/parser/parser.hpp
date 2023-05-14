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
    void find_var_val_statement(funscope* funscope);
    expression* find_expression();
    expression* find_binary_math_expression();
    expression* find_binary_math_plus_minus_expression();
    expression* find_binary_math_star_slash_expression();
    expression* find_binary_math_exponent_expression();
    expression* find_binary_math_parentheses_expression();

public:
    parser(std::vector<lexertoken>* tokens);
    void startparse(globalscope globalscope);
};
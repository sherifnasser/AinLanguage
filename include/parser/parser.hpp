#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "LexerToken.hpp"
#include "globalscope.hpp"
#include "expression.hpp"
class parser
{
private:
    std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> tokens;
    LexerToken current;
    int currentpos=-1;
    LexerToken next();
    bool currentmatch(LexerToken expected);
    bool nextmatch(LexerToken expected);
    std::wstring currentval();
    void find_functions(globalscope* globalscope);
    statement* find_next_statement(funscope* funscope);
    statement* find_var_val_statement(funscope* funscope);
    statement* find_var_reassign_statement(funscope* funscope);
    statement* find_return_statement(funscope* funscope);
    statement* find_expression_statement(funscope* funscope);
    statement* find_if_statement(funscope* funscope);
    statement* find_while_statement(funscope* funscope);
    statement* find_do_while_statement(funscope* funscope);
    expression* find_expression();
    expression* find_binary_logical_or_expression();
    expression* find_binary_logical_and_expression();
    expression* find_binary_equality_expression();
    expression* find_binary_comparison_expression();
    expression* find_binary_math_plus_minus_expression();
    expression* find_binary_math_star_slash_expression();
    expression* find_binary_math_exponent_expression();
    expression* find_binary_parentheses_expression();
    void add_next_stm_to_stm_list(funscope* fscope,StmList* stmlist);

public:
    parser(std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> tokens);
    void startparse(globalscope* globalscope);
};
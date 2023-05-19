#pragma once
#include <iostream>
#include "lexertoken.hpp"
class symboltoken:public lexertoken
{
    
public:
    symboltoken(std::wstring c);
    static symboltoken LEFT_ANGLE_BRACKET;
    static symboltoken RIGHT_ANGLE_BRACKET;
    static symboltoken LEFT_PARENTHESIS;
    static symboltoken RIGHT_PARENTHESIS;
    static symboltoken LEFT_CURLY_BRACES;
    static symboltoken RIGHT_CURLY_BRACES;
    static symboltoken LEFT_SQUARE_BRACKET;
    static symboltoken RIGHT_SQUARE_BRACKET;

    static symboltoken COMMA;
    static symboltoken COLON;
    static symboltoken SEMICOLON;

    static symboltoken QUESTION_MARK;
    static symboltoken EXCLAMATION_MARK;
    static symboltoken AMPERSAND;
    static symboltoken BAR;
    static symboltoken DOT;
    static symboltoken DOUBLE_QUOTE;
    static symboltoken SINGLE_QUOTE;
    static symboltoken BACK_SLASH;

    static symboltoken PLUS;
    static symboltoken MINUS;
    static symboltoken STAR;
    static symboltoken SLASH;
    static symboltoken EQUAL;
    static symboltoken MODULO;
    static symboltoken POWER;

    static symboltoken GREATER_EQUAL;
    static symboltoken LESS_EQUAL;
    static symboltoken EQUAL_EQUAL;
    static symboltoken NOT_EQUAL;
    static symboltoken LOGICAL_AND;
    static symboltoken LOGICAL_OR;
};
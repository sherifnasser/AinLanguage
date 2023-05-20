#include "symboltoken.hpp"

symboltoken::symboltoken(std::wstring c):
lexertoken(lexertoken::SYMBOL_TOKEN,c){}

symboltoken symboltoken::LEFT_ANGLE_BRACKET=symboltoken(L"<");
symboltoken symboltoken::RIGHT_ANGLE_BRACKET=symboltoken(L">");
symboltoken symboltoken::LEFT_PARENTHESIS=symboltoken(L"(");
symboltoken symboltoken::RIGHT_PARENTHESIS=symboltoken(L")");
symboltoken symboltoken::LEFT_CURLY_BRACES=symboltoken(L"{");
symboltoken symboltoken::RIGHT_CURLY_BRACES=symboltoken(L"}");
symboltoken symboltoken::LEFT_SQUARE_BRACKET=symboltoken(L"[");
symboltoken symboltoken::RIGHT_SQUARE_BRACKET=symboltoken(L"]");
symboltoken symboltoken::COMMA=symboltoken(L"،");
symboltoken symboltoken::COLON=symboltoken(L":");
symboltoken symboltoken::SEMICOLON=symboltoken(L"؛");

symboltoken symboltoken::QUESTION_MARK=symboltoken(L"؟");
symboltoken symboltoken::EXCLAMATION_MARK=symboltoken(L"!");
symboltoken symboltoken::AMPERSAND=symboltoken(L"&");
symboltoken symboltoken::BAR=symboltoken(L"|");
symboltoken symboltoken::DOT=symboltoken(L".");
symboltoken symboltoken::DOUBLE_QUOTE=symboltoken(L"\"");
symboltoken symboltoken::SINGLE_QUOTE=symboltoken(L"\"");
symboltoken symboltoken::BACK_SLASH=symboltoken(L"\\");

symboltoken symboltoken::PLUS=symboltoken(L"+");
symboltoken symboltoken::MINUS=symboltoken(L"-");
symboltoken symboltoken::STAR=symboltoken(L"*");
symboltoken symboltoken::SLASH=symboltoken(L"/");
symboltoken symboltoken::EQUAL=symboltoken(L"=");
symboltoken symboltoken::MODULO=symboltoken(L"%");
symboltoken symboltoken::POWER=symboltoken(L"^");

symboltoken symboltoken::GREATER_EQUAL=symboltoken(L">=");
symboltoken symboltoken::LESS_EQUAL=symboltoken(L"<=");
symboltoken symboltoken::EQUAL_EQUAL=symboltoken(L"==");
symboltoken symboltoken::NOT_EQUAL=symboltoken(L"!=");
symboltoken symboltoken::LOGICAL_AND=symboltoken(L"&&");
symboltoken symboltoken::LOGICAL_OR=symboltoken(L"||");
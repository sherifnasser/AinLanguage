#pragma once
#include<map>
class lexertoken{
public:
    enum TOKEN_TYPE : int
    {
        NOT_SET_TOKEN = -1,
        SYMBOL_TOKEN = 0,
        LITERAL_TOKEN = 1,
        COMMENT_TOKEN = 2,
        KEYWORD_TOKEN = 3,
        IDENTIFIER_TOKEN = 4
    };

    enum LITERAL : int{
        STRING=0,
        NUMBER=1,
        BOOL=2
    };

    lexertoken(TOKEN_TYPE tokentype, std::wstring val);
    TOKEN_TYPE gettokentype();
    std::wstring getval();
    bool operator== (lexertoken &token);

private:
    TOKEN_TYPE tokentype;
    std::wstring val;
};

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
    lexertoken();
    lexertoken(TOKEN_TYPE tokentype, std::wstring val);
    TOKEN_TYPE gettokentype();
    std::wstring getval();
    bool operator== (lexertoken &token);
    bool operator!= (lexertoken &token);
    bool isidentifiertoken();
    bool isnotsettoken();
    bool isnumberliteral();
    bool isintliteral();
    bool islongliteral();
    bool isfloatliteral();
    bool isdoubleliteral();
    bool ischarliteral();
    bool isstringliteral();
    static lexertoken identifiertoken;
    static lexertoken notsettoken;
    
private:
    TOKEN_TYPE tokentype;
    std::wstring val;
};

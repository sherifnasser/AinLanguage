#pragma once
#include<map>

class LexerToken{
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

    LexerToken();
    LexerToken(TOKEN_TYPE tokenType, std::wstring val);
    TOKEN_TYPE getTokenType();
    std::wstring getVal();
    bool operator== (LexerToken &token) const;
    bool operator!= (LexerToken &token) const;
    bool isidentifiertoken();
    bool isnotsettoken();
    bool isnumberliteral();
    bool isintliteral();
    bool islongliteral();
    bool isfloatliteral();
    bool isdoubleliteral();
    bool ischarliteral();
    bool isstringliteral();
    static LexerToken identifiertoken;
    static LexerToken notsettoken;
    virtual ~LexerToken();
private:
    TOKEN_TYPE tokenType;
    std::wstring val;
};

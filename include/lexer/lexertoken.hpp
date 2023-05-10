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

    enum SYMBOL : char
    {
        NOT_IN_AIN=' ',

        LEFT_ANGLE_BRACKET='<',
        RIGHT_ANGLE_BRACKET='>',
        LEFT_PARENTHESIS='(',
        RIGHT_PARENTHESIS=')',
        LEFT_CURLY_BRACES='{',
        RIGHT_CURLY_BRACES='}',
        LEFT_SQUARE_BRACKET='[',
        RIGHT_SQUARE_BRACKET=']',
        COLON=':',
        TILDE='~',

        HASH='#',
        EXCLAMATION_MARK='!',
        AMPERSAND='&',
        BAR='|',
        DOT='.',
        UNDERSCORE='_',
        DOUBLE_QUOTE='\"',
        SINGLE_QUOTE='\'',
        BACK_SLASH='\\',

        PLUS='+',
        MINUS='-',
        STAR='*',
        SLASH='/',
        EQUAL='=',
        TRIAL_DIVISION='%',
        POWER='^',
    };

    enum LITERAL : int{
        STRING=0,
        NUMBER=1,
        BOOL=2
    };

    enum KEYWORD{
        VAR,
        VAL,
        FUN,
        RETURN,
        CLASS,
        PUBLIC,
        PRIVATE,
    // static const std::string PROTECTED = "TODO";
        IF,
        ELSE_IF,
        ELSE,
        WHEN, // as switch
        FOR,
        WHILE
    };

    lexertoken(TOKEN_TYPE tokentype, std::string &val);
    TOKEN_TYPE gettokentype();
    std::string getval();
    bool iskeyword();

private:
    TOKEN_TYPE tokentype;
    std::string val;
};


namespace TOKENS{
    static const std::map<lexertoken::KEYWORD,std::string> KEYWORDS{
        {lexertoken::KEYWORD::VAR,"متغير"},
        {lexertoken::KEYWORD::FUN,"دالة"},
        {lexertoken::KEYWORD::RETURN,"بقيمة"},
        {lexertoken::KEYWORD::CLASS,"تصنيف"},
        {lexertoken::KEYWORD::PUBLIC,"تعميم"},
        {lexertoken::KEYWORD::PRIVATE,"تخصيص"},
        // {lexertoken::KEYWORD::PROTECTED,"تخصيص"}, TODO
        
        {lexertoken::KEYWORD::IF,"لو"},
        {lexertoken::KEYWORD::ELSE_IF,"لكن لو"},
        {lexertoken::KEYWORD::ELSE,"وإلا"},
        {lexertoken::KEYWORD::WHEN,"عندما"}, // as switch

        {lexertoken::KEYWORD::FOR,"لأجل"},
        {lexertoken::KEYWORD::WHILE,"طالما"},
    };

};

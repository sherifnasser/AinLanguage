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

    enum SYMBOL : wchar_t
    {
        NOT_IN_AIN=L' ',

        LEFT_ANGLE_BRACKET=L'<',
        RIGHT_ANGLE_BRACKET=L'>',
        LEFT_PARENTHESIS=L'(',
        RIGHT_PARENTHESIS=L')',
        LEFT_CURLY_BRACES=L'{',
        RIGHT_CURLY_BRACES=L'}',
        LEFT_SQUARE_BRACKET=L'[',
        RIGHT_SQUARE_BRACKET=L']',
        COLON=L':',
        TILDE=L'~',

        HASH=L'#',
        EXCLAMATION_MARK=L'!',
        AMPERSAND=L'&',
        BAR=L'|',
        DOT=L'.',
        DOUBLE_QUOTE=L'\"',
        SINGLE_QUOTE=L'\'',
        BACK_SLASH=L'\\',

        PLUS=L'+',
        MINUS=L'-',
        STAR=L'*',
        SLASH=L'/',
        EQUAL=L'=',
        TRIAL_DIVISION=L'%',
        POWER=L'^',
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

        PACKAGE,
        IMPORT,
        CLASS,
        INTERFACE,
        OBJECT,

        DATA,
        ABSTRACT,
        OPEN,
        ENUM,
        ANNOTATION,

        PUBLIC,
        PRIVATE,
        PROTECTED,
        OVERRIDE,

        IF,
        ELSE_IF,
        ELSE,
        WHEN, // as switch

        FOR,
        WHILE,
        BREAK,
        CONTINUE
    };

    lexertoken(TOKEN_TYPE tokentype, std::wstring &val);
    TOKEN_TYPE gettokentype();
    std::wstring getval();
    bool iskeyword();
    static bool iskeyword(std::wstring &val);

private:
    TOKEN_TYPE tokentype;
    std::wstring val;
};


namespace TOKENS{
    static const std::map<lexertoken::KEYWORD,std::wstring> KEYWORDS{
        {lexertoken::KEYWORD::VAR,L"متغير"},
        {lexertoken::KEYWORD::VAL,L"ثابت"},
        {lexertoken::KEYWORD::FUN,L"دالة"},
        {lexertoken::KEYWORD::RETURN,L"بقيمة"},

        {lexertoken::KEYWORD::PACKAGE,L"تصنيف"},
        {lexertoken::KEYWORD::IMPORT,L"استيراد"},
        {lexertoken::KEYWORD::CLASS,L"تصنيف"},
        {lexertoken::KEYWORD::INTERFACE,L"نموذج"},
        {lexertoken::KEYWORD::OBJECT,L"كائن"},

        {lexertoken::KEYWORD::DATA,L"بيانات"},
        {lexertoken::KEYWORD::ABSTRACT,L"مجرد"},
        {lexertoken::KEYWORD::OPEN,L"مفتوح"},
        // TODO -> find them in arabic keywords
        {lexertoken::KEYWORD::ENUM,L"enum"},
        {lexertoken::KEYWORD::ANNOTATION,L"annotation"},

        {lexertoken::KEYWORD::PUBLIC,L"تعميم"},
        {lexertoken::KEYWORD::PRIVATE,L"تخصيص"},
        {lexertoken::KEYWORD::PROTECTED,L"محمي"},
        {lexertoken::KEYWORD::OVERRIDE,L"override"},
        
        {lexertoken::KEYWORD::IF,L"لو"},
        {lexertoken::KEYWORD::ELSE_IF,L"لكن لو"},
        {lexertoken::KEYWORD::ELSE,L"وإلا"},
        {lexertoken::KEYWORD::WHEN,L"عندما"}, // as switch

        {lexertoken::KEYWORD::FOR,L"لأجل"},
        {lexertoken::KEYWORD::WHILE,L"طالما"},
        {lexertoken::KEYWORD::BREAK,L"اكسر"},
        {lexertoken::KEYWORD::CONTINUE,L"تخطى"},
    };

};

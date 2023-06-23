#include "LexerToken.hpp"
#include "SharedPtrTypes.hpp"
template<typename T>
class BaseParser{
    protected:
        SharedLinkedListNode<SharedLexerToken> current;
        SharedScope scope;
    public:
        BaseParser<T>(
            SharedLinkedListNode<SharedLexerToken> current,
            SharedScope scope
        );
        virtual T parse()=0;

    private:
        SharedLexerToken next();
        bool currentMatch(LexerToken expected);
        bool nextMatch(LexerToken expected);
        SharedLexerToken currentToken();
        std::wstring currentVal();
        LexerToken::TOKEN_TYPE currentTokenType();
};
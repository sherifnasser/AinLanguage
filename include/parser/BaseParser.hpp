#include "LexerToken.hpp"
#include "SharedPtrTypes.hpp"
#include "LinkedList.hpp"

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
        BaseParser<T>(
            SharedLinkedList<SharedLexerToken> list,
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

template<typename T>
BaseParser<T>::BaseParser(
    SharedLinkedListNode<SharedLexerToken> current,
    SharedScope scope
):current(current),scope(scope){}

template<typename T>
BaseParser<T>::BaseParser(
    SharedLinkedList<SharedLexerToken> list,
    SharedScope scope
):current(list->head),scope(scope){}

template<typename T>
SharedLexerToken BaseParser<T>::next(){
    current=current->next;
    auto tokenType=currentTokenType();
    // skip those
    if(
        tokenType!=LexerToken::COMMENT_TOKEN
        &&
        tokenType!=LexerToken::SPACE_TOKEN
        &&
        tokenType!=LexerToken::EOL_TOKEN
    )
        return currentToken();
    
    return next();
}

template<typename T>
bool BaseParser<T>::currentMatch(LexerToken expected){
    return *currentToken()==expected;
}

template<typename T>
bool BaseParser<T>::nextMatch(LexerToken expected){
    next();
    return currentMatch(expected);
}

template<typename T>
SharedLexerToken BaseParser<T>::currentToken(){
    return (current)
    ?current->val
    :std::make_shared<LexerToken>(LexerToken(LexerToken::EOF_TOKEN,L""));
}

template<typename T>
std::wstring BaseParser<T>::currentVal(){
    return currentToken()->getVal();
}

template<typename T>
LexerToken::TOKEN_TYPE BaseParser<T>::currentTokenType(){
    return currentToken()->getTokenType();
}

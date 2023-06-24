#include "TokensIteratorForTests.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>

TokensIterator getTokensIterator(
    std::vector<LexerToken> tokens
){
    auto list=LinkedList<SharedLexerToken>();
    for(auto &token:tokens){
        list.insert(
            std::make_shared<LexerToken>(token)
        );
    }
    return TokensIterator(list);
}
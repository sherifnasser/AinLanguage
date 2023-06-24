#pragma once
#include "LexerToken.hpp"
#include "TokensIterator.hpp"
#include <vector>
TokensIterator getTokensIterator(
    std::vector<LexerToken> tokens
);
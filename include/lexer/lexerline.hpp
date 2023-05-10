#pragma once
#include <iostream>
#include <vector>
#include "lexertoken.hpp"

class lexerline{
    private:
        std::vector<lexertoken> *tokens;
        int linenumber;
    public:
        lexerline(int linenumber);
        std::vector<lexertoken>* gettokens();
        int getlinenumber();
};

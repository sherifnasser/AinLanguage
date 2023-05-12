#pragma once
#include <iostream>
#include <vector>
#include "lexertoken.hpp"
#include "globalscope.hpp"
class parser
{
private:
    std::vector<lexertoken>* tokens;
    
    void findglobalfunctions(globalscope &globalscope);
public:
    parser(std::vector<lexertoken>* tokens);
    void startparse(globalscope globalscope);
};
#include<iostream>
#include<vector>
#include "lexerline.hpp"

lexerline::lexerline(int linenumber):linenumber(linenumber){
    tokens=new std::vector<lexertoken>();
}

std::vector<lexertoken>* lexerline::gettokens(){
    return tokens;
}

int lexerline::getlinenumber(){
    return this->linenumber;
}

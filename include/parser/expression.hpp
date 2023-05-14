#pragma once
#include "lexertoken.hpp"
class expression{
    public:
        virtual void print(wstring &tabsize)=0;
};

class numberexpression:public expression{
    private:
        wstring val;
    public:
        numberexpression(wstring &val);
        void print(wstring &tabsize) override;
};

class binarymathxpression:public expression{
    private:
        expression* left;
        lexertoken operation;
        expression* right;
    public:
        binarymathxpression(expression* left, lexertoken &operation, expression* right);
        void print(wstring &tabsize) override;
};
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

class binaryexpression:public expression{
    private:
        expression* left;
        lexertoken operation;
        expression* right;
    public:
        binaryexpression(expression* left, lexertoken &operation, expression* right);
        void print(wstring &tabsize) override;
};

class variableaccessexpression:public expression{
    private:
        wstring name;
    public:
        variableaccessexpression(wstring &name);
        void print(wstring &tabsize) override;
};

class funcallexpression:public expression{
    private:
        wstring funname;
        std::vector<expression*>* argsexpressions;
    public:
        funcallexpression(wstring &funname, std::vector<expression*>* argsexpressions);
        void print(wstring &tabsize) override;
};
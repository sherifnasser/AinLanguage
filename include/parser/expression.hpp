#pragma once
#include "lexertoken.hpp"
class expression{
    public:
        virtual wstring evaluate()=0;
        virtual void print(wstring &tabsize)=0;
};

class numberexpression:public expression{
    private:
        wstring val;
    public:
        numberexpression(wstring &val);
        wstring evaluate() override;
        void print(wstring &tabsize) override;
};

class binaryexpression:public expression{
    private:
        expression* left;
        lexertoken operation;
        expression* right;
    public:
        binaryexpression(expression* left, lexertoken &operation, expression* right);
        wstring evaluate() override;
        void print(wstring &tabsize) override;
        wstring evaluateplus(wstring l, wstring r);
        wstring evaluateminus(wstring l, wstring r);
        wstring evaluatestar(wstring l, wstring r);
        wstring evaluateslash(wstring l, wstring r);
        wstring evaluatemodulo(wstring l, wstring r);
        wstring evaluatepower(wstring l, wstring r);
};

class variableaccessexpression:public expression{
    private:
        wstring name;
    public:
        variableaccessexpression(wstring &name);
        wstring evaluate() override;
        void print(wstring &tabsize) override;
};

class funcallexpression:public expression{
    private:
        wstring funname;
        std::vector<expression*>* argsexpressions;
    public:
        funcallexpression(wstring &funname, std::vector<expression*>* argsexpressions);
        wstring evaluate() override;
        void print(wstring &tabsize) override;
};
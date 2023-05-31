#pragma once
#include "scope.hpp"
#include "LexerToken.hpp"

class scope;
class variable;
class constant;
class funscope;
class classscope;

class expression{
    public:
        virtual std::wstring evaluate(scope* evalscope)=0;
        virtual void print(std::wstring tabsize=L"")=0;
};

class boolexpression:public expression{
    private:
        std::wstring val;
    public:
        boolexpression(std::wstring &val);
        std::wstring evaluate(scope* evalscope) override;
        void print(std::wstring tabsize=L"") override;
        static bool boolfromstr(std::wstring s);
        static std::wstring strfrombool(bool b);
};


class stringexpression:public expression{
    private:
        std::wstring val;
    public:
        stringexpression(std::wstring &val);
        std::wstring evaluate(scope* evalscope) override;
        void print(std::wstring tabsize=L"") override;
};

class numberexpression:public expression{
    private:
        std::wstring val;
    public:
        numberexpression(std::wstring &val);
        std::wstring evaluate(scope* evalscope) override;
        void print(std::wstring tabsize=L"") override;
};

class binaryexpression:public expression{
    private:
        expression* left;
        LexerToken operation;
        expression* right;
    public:
        binaryexpression(expression* left, LexerToken &operation, expression* right);
        std::wstring evaluate(scope* evalscope) override;
        void print(std::wstring tabsize=L"") override;
        std::wstring evaluatelogicalor(std::wstring l, std::wstring r);
        std::wstring evaluatelogicaland(std::wstring l, std::wstring r);
        std::wstring evaluateequalequal(std::wstring l, std::wstring r);
        std::wstring evaluatenotequal(std::wstring l, std::wstring r);
        std::wstring evaluategreaterequal(std::wstring l, std::wstring r);
        std::wstring evaluatelessequal(std::wstring l, std::wstring r);
        std::wstring evaluategreater(std::wstring l, std::wstring r);
        std::wstring evaluateless(std::wstring l, std::wstring r);
        std::wstring evaluateplus(std::wstring l, std::wstring r);
        std::wstring evaluateminus(std::wstring l, std::wstring r);
        std::wstring evaluatestar(std::wstring l, std::wstring r);
        std::wstring evaluateslash(std::wstring l, std::wstring r);
        std::wstring evaluatemodulo(std::wstring l, std::wstring r);
        std::wstring evaluatepower(std::wstring l, std::wstring r);
};

class variableaccessexpression:public expression{
    private:
        std::wstring name;
    public:
        variableaccessexpression(std::wstring &name);
        std::wstring evaluate(scope* evalscope) override;
        void print(std::wstring tabsize=L"") override;
};

class funcallexpression:public expression{
    private:
        std::wstring funname;
        std::vector<expression*>* argsexpressions;
    public:
        funcallexpression(std::wstring &funname, std::vector<expression*>* argsexpressions);
        std::wstring evaluate(scope* evalscope) override;
        void print(std::wstring tabsize=L"") override;
};
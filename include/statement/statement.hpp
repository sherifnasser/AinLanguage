#pragma once
#include "scope.hpp"

class expression;
class scope;
class variable;
class constant;
class funscope;
class classscope;

class statement
{
    protected:
        scope* runscope;
    public:
        statement(scope* runscope);
        virtual void run()=0;
};

class expressionstatement:public statement
{
    private:
        expression* ex;
    public:
        expressionstatement(scope* runscope,expression* ex);
        void run() override;
};

class vardeclarationstatement:public statement
{
    private:
        variable* var;
        expression* ex;
    public:
        vardeclarationstatement(scope* runscope,variable* var,expression* ex);
        void run() override;
};

class varreassignstatement:public statement
{
    private:
        std::wstring varname;
        expression* ex;
    public:
        varreassignstatement(scope* runscope,std::wstring varname,expression* ex);
        void run() override;
};


class returnstatement:public statement
{
    private:
        expression* ex;
    public:
        returnstatement(funscope* runscope,expression* ex);
        void run() override;
};


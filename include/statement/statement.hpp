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

class vardeclarationstatement:public statement
{
    private:
        variable* var;
        expression* ex;
    public:
        vardeclarationstatement(scope* runscope,variable* var,expression* ex);
        void run() override;
};


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

typedef std::vector<statement*> StmList;
typedef std::pair<expression*,StmList*> ExStmList;

class ifstatement:public statement
{
    private:
        // Maybe change if we removed ELSE_IF keyword token
        std::vector<ExStmList*>* exstmlists;
    public:
        ifstatement(funscope* runscope,std::vector<ExStmList*>* exstmlists);
        void run() override;
};

class whilestatement:public statement
{
    protected:
        expression* ex;
        StmList* stmlist;

    public:
        whilestatement(funscope* runscope, expression* ex, StmList* stmlist);
        void run() override;
};

class dowhilestatement:public whilestatement
{
    public:
        dowhilestatement(funscope* runscope, expression* ex, StmList* stmlist);
        void run() override;
};

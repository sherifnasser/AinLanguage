#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "expression.hpp"
#include "statement.hpp"

class statement;
class scope;
class variable;
class constant;
class funscope;
class classscope;


class scope
{
    protected:
        scope* parentscope;

        std::wstring name;

        // accessiable variables
        std::vector<variable*>* vars;

        // accessiable constants
        std::vector<constant*>* vals;

        // accessiable functions
        std::vector<funscope*>* funs;  // TODO: sort them and use binary search

        // accessiable classess
        std::vector<classscope*>* classes;

    public:
        void setparentscope(scope* parentscope);
        void setvars(std::vector<variable*>* vars);
        void setvals(std::vector<constant*>* vals);
        void setfuns(std::vector<funscope*>* funs);
        void setclasses(std::vector<classscope*>* classes);

        scope* getparentscope();
        std::vector<variable*>* getvars();
        std::vector<constant*>* getvals();
        std::vector<funscope*>* getfuns();
        std::vector<classscope*>* getclasses();
        variable* getvarbyname(std::wstring varname);
        funscope* getfunbyname(std::wstring funname);
        std::wstring getname();
        virtual ~scope();
};



class classscope: public scope
{
};



class funscope:public scope
{
    private:
        std::wstring returntype;
        std::wstring returnvalue;
        std::vector<std::pair<std::wstring,std::wstring>>* args;
        std::vector<statement*>* stmlist;
        void init();
    public:
        funscope(scope* parentscope, std::wstring &name, std::wstring &returntype,std::vector<std::pair<std::wstring,std::wstring>>* args);
        std::wstring getreturntype();
        std::vector<std::pair<std::wstring,std::wstring>>* getargs();
        void setstmlist(std::vector<statement*>* stmlist);
        std::vector<statement*>* getstmlist();
        void call();
        std::wstring getreturnvalue();
        void setreturnvalue(std::wstring returnvalue);
        
};



class variable
{
protected:
    scope *parentscope;
    std::wstring name;
    std::wstring type;
    std::wstring currentval;
    bool isinitialized=false;

    public:
        variable(scope* parentscope, std::wstring &name, std::wstring &type);
        std::wstring getname();
        std::wstring gettype();
        std::wstring getcurrentvalue();
        virtual void setcurrentvalue(std::wstring value);
};



class constant : public variable
{
    public:
        constant(scope* parentscope, std::wstring &name, std::wstring &type);
        void setcurrentvalue(std::wstring value) override;
};

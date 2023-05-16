#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "expression.hpp"
#define wstring std::wstring

class scope;
class variable;
class constant;
class funscope;
class classscope;


class scope
{
    protected:
        scope* parentscope;

        wstring name;

        // accessiable variables
        std::vector<variable>* vars;

        // accessiable constants
        std::vector<constant>* vals;

        // accessiable functions
        std::vector<funscope>* funs;

        // accessiable classess
        std::vector<classscope>* classes;

    public:
        void setparentscope(scope* parentscope);
        void setvars(std::vector<variable>* vars);
        void setvals(std::vector<constant>* vals);
        void setfuns(std::vector<funscope>* funs);
        void setclasses(std::vector<classscope>* classes);

        scope* getparentscope();
        std::vector<variable>* getvars();
        std::vector<constant>* getvals();
        std::vector<funscope>* getfuns();
        std::vector<classscope>* getclasses();
        wstring getname();
};



class classscope: public scope
{
};



class funscope:public scope
{
    private:
        wstring returntype;
        std::vector<std::pair<wstring,wstring>>* args;
        void init();
    public:
        funscope(wstring &name, wstring &returntype,std::vector<std::pair<wstring,wstring>>* args);
        wstring getreturntype();
        std::vector<std::pair<wstring,wstring>>* getargs();
        
};



class variable
{
protected:
    scope *parentscope;
    wstring name;
    wstring type;
    expression* ex;

    public:
        variable(scope* parentscope, wstring &name, wstring &type);
        variable(scope* parentscope, wstring &name, expression* ex);
        variable(scope* parentscope, wstring &name, wstring &type, expression* ex);
        wstring getname();
        wstring gettype();
        expression* getexpression();
};



class constant : public variable
{
    public:
        constant(scope* parentscope, wstring &name, wstring &type);
        constant(scope* parentscope, wstring &name, expression* ex);
        constant(scope* parentscope, wstring &name, wstring &type, expression* ex);
};
#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "expression.hpp"
#include "statement.hpp"
#define wstring std::wstring

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

        wstring name;

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
        variable* getvarbyname(wstring varname);
        funscope* getfunbyname(wstring funname);
        wstring getname();
        virtual ~scope();
};



class classscope: public scope
{
};



class funscope:public scope
{
    private:
        wstring returntype;
        wstring returnvalue;
        std::vector<std::pair<wstring,wstring>>* args;
        std::vector<statement*>* stmlist;
        void init();
    public:
        funscope(scope* parentscope, wstring &name, wstring &returntype,std::vector<std::pair<wstring,wstring>>* args);
        wstring getreturntype();
        std::vector<std::pair<wstring,wstring>>* getargs();
        void setstmlist(std::vector<statement*>* stmlist);
        std::vector<statement*>* getstmlist();
        void call();
        wstring getreturnvalue();
        void setreturnvalue(wstring returnvalue);
        
};



class variable
{
protected:
    scope *parentscope;
    wstring name;
    wstring type;
    wstring currentval;
    bool isinitialized=false;

    public:
        variable(scope* parentscope, wstring &name, wstring &type);
        wstring getname();
        wstring gettype();
        wstring getcurrentvalue();
        virtual void setcurrentvalue(wstring value);
};



class constant : public variable
{
    public:
        constant(scope* parentscope, wstring &name, wstring &type);
        void setcurrentvalue(wstring value) override;
};

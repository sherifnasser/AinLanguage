#pragma once
#include <iostream>
#include <map>
#include <vector>
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
};



class classscope: public scope
{
};



class funscope:public scope
{
    private:
        wstring returntype;
        std::map<wstring,wstring>* args;
    public:
        funscope(wstring &name, wstring &returntype,std::map<wstring,wstring>* args);
        funscope(wstring &name, wstring &returntype);
        funscope(wstring &name, std::map<wstring,wstring>* args);
        funscope(wstring &name);
};



class variable
{
protected:
    scope *parentscope;
    wstring *name;
    classscope *type;

public:
    variable();
};



class constant : public variable
{
};

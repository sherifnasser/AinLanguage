#pragma once
#include <iostream>
#include <vector>

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
    std::vector<variable>* vars;

    // accessiable constants
    std::vector<constant>* vals;

    // accessiable functions
    std::vector<funscope>* funs;

    // accessiable classess
    std::vector<classscope>* classess;

public:
    void setparentscope(scope* parentscope);
    void setvars(std::vector<variable>* vars);
    void setvals(std::vector<constant>* vals);
    void setfuns(std::vector<funscope>* funs);
    void setclasses(std::vector<classscope>* classess);

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
};



class variable
{
protected:
    scope *parentscope;
    std::wstring *name;
    classscope *type;

public:
    variable();
};



class constant : public variable
{
};

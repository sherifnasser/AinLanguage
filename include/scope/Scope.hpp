#pragma once
#include "SharedPtrTypes.hpp"

class Scope
{
    protected:
        SharedScope parentScope;

        std::wstring name;

        // accessiable variables
        SharedVector<SharedVariable> vars;

        // accessiable constants
        SharedVector<SharedConstant> vals;

        // accessiable functions
        SharedVector<SharedFunScope> funs;  // TODO: sort them and use binary search

        // accessiable classess
        SharedVector<SharedClassScope> classes;

    public:
        void setParentScope(SharedScope parentScope);
        void setVars(SharedVector<SharedVariable> vars);
        void setVals(SharedVector<SharedConstant> vals);
        void setFuns(SharedVector<SharedFunScope> funs);
        void setClasses(SharedVector<SharedClassScope> classes);

        SharedScope getparentScope();
        SharedVector<SharedVariable> getVars();
        SharedVector<SharedConstant> getVals();
        SharedVector<SharedFunScope> getFuns();
        SharedVector<SharedClassScope> getClasses();
        SharedVariable getVarByName(std::wstring varname);
        SharedFunScope getFunByName(std::wstring funName);
        std::wstring getName();
        virtual ~Scope();
};
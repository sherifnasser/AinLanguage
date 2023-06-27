#pragma once
#include "SharedPtrTypes.hpp"

class Scope
{
    protected:
        SharedScope parentScope;

        std::wstring name;

        // accessiable OldVariables
        SharedVector<SharedOldVariable> vars;

        // accessiable OldConstants
        SharedVector<SharedOldConstant> vals;

        // accessiable functions
        SharedVector<SharedOldFunScope> funs;  // TODO: sort them and use binary search

        // accessiable classess
        SharedVector<SharedClassScope> classes;

    public:
        void setParentScope(SharedScope parentScope);
        void setVars(SharedVector<SharedOldVariable> vars);
        void setVals(SharedVector<SharedOldConstant> vals);
        void setFuns(SharedVector<SharedOldFunScope> funs);
        void setClasses(SharedVector<SharedClassScope> classes);

        SharedScope getparentScope();
        SharedVector<SharedOldVariable> getVars();
        SharedVector<SharedOldConstant> getVals();
        SharedVector<SharedOldFunScope> getFuns();
        SharedVector<SharedClassScope> getClasses();
        SharedOldVariable getVarByName(std::wstring varname);
        SharedOldFunScope getFunByName(std::wstring funName);
        std::wstring getName();
        virtual ~Scope();
};
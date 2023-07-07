#pragma once
// TODO: change name
#include "SharedPtrTypes.hpp"
#include <string>
class BaseScope{
protected:
    SharedBaseScope parentScope;

    std::wstring name;
public:
    BaseScope(std::wstring name,SharedBaseScope parentScope);
    SharedBaseScope getParentScope();
    std::wstring getName();
    virtual ~BaseScope();
    virtual SharedClassScope getClassByType(SharedType type);
    virtual SharedVariable getVarByName(std::wstring varName);
    virtual SharedVariable getFunByDecl(SharedFunDecl funDecl);
    static SharedFunScope toFunScope(SharedBaseScope scope);
    static SharedClassScope toClassScope(SharedBaseScope scope);
    static SharedFileScope toFileScope(SharedBaseScope scope);
    static SharedFunScope getContainingFun(SharedStmListScope stmListScope);
    static SharedClassScope getContainingClass(SharedBaseScope scope);
    static SharedFileScope getContainingFile(SharedBaseScope scope);
};
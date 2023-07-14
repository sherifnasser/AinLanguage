#pragma once
#include "BaseScope.hpp"
#include "SharedPtrTypes.hpp"
class ClassScope: public BaseScope{
    public:
        ClassScope(std::wstring name,SharedBaseScope parentScope);
        
        // TODO: add protected and static members

        // map fun decl to functions
        SharedMap<std::wstring,SharedFunScope> publicFunctions;
        SharedMap<std::wstring,SharedFunScope> privateFunctions;
        // map fun decl to functions
        SharedMap<std::wstring,SharedClassScope> publicClasses;
        SharedMap<std::wstring,SharedClassScope> privateClasses;
        // map variable names to variables
        SharedMap<std::wstring,SharedVariable> publicVariables;
        SharedMap<std::wstring,SharedVariable> privateVariables;

        SharedMap<std::wstring,SharedFunScope> getPublicFunctions() const;

        SharedMap<std::wstring,SharedFunScope> getPrivateFunctions() const;

        SharedMap<std::wstring,SharedClassScope> getPublicClasses() const;

        SharedMap<std::wstring,SharedClassScope> getPrivateClasses() const;

        SharedFunScope findPublicFunction(std::wstring decl);

        SharedFunScope findPrivateFunction(std::wstring decl);

        SharedVariable findPublicVariable(std::wstring varName);
        
        SharedVariable findPrivateVariable(std::wstring varName);
};
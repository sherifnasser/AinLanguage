#pragma once
#include "BaseScope.hpp"
#include "SharedPtrTypes.hpp"
class ClassScope: public BaseScope{
    public:
        ClassScope(std::wstring name,SharedBaseScope parentScope);

        void accept(ASTVisitor *visitor) override;
        
        // TODO: add protected and static members

        // map fun decl to functions
        SharedMap<std::wstring,SharedFunScope> publicFunctions;
        SharedMap<std::wstring,SharedFunScope> privateFunctions;

        // map constructor decl to constructors
        SharedMap<std::wstring,SharedConstructorScope> publicConstructors;
        SharedMap<std::wstring,SharedConstructorScope> privateConstructors;

        // map classes names to classes
        SharedMap<std::wstring,SharedClassScope> publicClasses;
        SharedMap<std::wstring,SharedClassScope> privateClasses;

        // map variable names to variables
        SharedMap<std::wstring,SharedVariable> publicVariables;
        SharedMap<std::wstring,SharedVariable> privateVariables;

        SharedStmListScope varsInitStmList;

        SharedMap<std::wstring,SharedFunScope> getPublicFunctions() const;

        SharedMap<std::wstring,SharedFunScope> getPrivateFunctions() const;

        SharedMap<std::wstring,SharedConstructorScope> getPublicConstructors() const;

        SharedMap<std::wstring,SharedConstructorScope> getPrivateConstructors() const;

        SharedMap<std::wstring,SharedClassScope> getPublicClasses() const;

        SharedMap<std::wstring,SharedClassScope> getPrivateClasses() const;

        SharedMap<std::wstring,SharedVariable> getPublicVariables()const;

        SharedMap<std::wstring,SharedVariable> getPrivateVariables()const;

        SharedFunScope findPublicFunction(std::wstring decl);

        SharedFunScope findPrivateFunction(std::wstring decl);

        SharedConstructorScope findPublicConstructor(std::wstring decl);

        SharedConstructorScope findPrivateConstructor(std::wstring decl);

        SharedVariable findPublicVariable(std::wstring varName);
        
        SharedVariable findPrivateVariable(std::wstring varName);

        SharedStmListScope getVarsInitStmList()const;

        void setVarsInitStmList(SharedStmListScope varsInitStmList);

        void runVarsInitStmList();

        void pushNewProperties();

        SharedMap<std::wstring, SharedIValue> popLastProperties();
};
#include "TypeChecker.hpp"
#include "BaseScope.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "FileScope.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace Semantics {

    TypeChecker::TypeCheckStatement::TypeCheckStatement(
        int lineNumber,
        SharedBaseScope searchScope,
        SharedType type
    ):lineNumber(lineNumber),searchScope(searchScope),type(type){}

    TypeChecker::TypeChecker(){}

    std::shared_ptr<TypeChecker> TypeChecker::getInstance(){
        if(!instance){
            TypeChecker tc;
            instance=std::make_shared<TypeChecker>(tc);
        }
        return instance;
    }

    void TypeChecker::subscribe(int lineNumber,SharedBaseScope searchScope,SharedType type){
        checkStatements.push_back(
            TypeCheckStatement(
                lineNumber,searchScope,type
            )
        );
    }

    void TypeChecker::check(){
        std::wstring diagnostics;

        for(auto& stm:checkStatements){
            auto classScope=stm.searchScope->getClassByType(stm.type);
            if(classScope){
                stm.type->setClassScope(classScope);
                return;
            }
            SharedFileScope fileScope;
            auto parentScope=stm.searchScope->getParentScope();
            while(!(fileScope=std::dynamic_pointer_cast<FileScope>(parentScope))){
                parentScope=parentScope->getParentScope();
            }

            diagnostics.append(
                 L"لم يتم العثور على هذا النوع "+
                 *stm.type->getName()
                 +L"\n\tفي الملف "+fileScope->getName()+
                 L"\nفي السطر "+
                 std::to_wstring(stm.lineNumber)
                 +L"\n\n----------------------------------------------\n\n"
            );
        }

        std::wcout<<diagnostics;
    }

}
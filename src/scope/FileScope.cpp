#include "FileScope.hpp"
#include "FunctionNotFoundException.hpp"
#include "PackageScope.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include <memory>
#include <string>

FileScope::FileScope(std::wstring filePath,SharedPackageScope parentScope)
:BaseScope(filePath,parentScope),
publicFunctions(std::make_shared<std::map<std::wstring,SharedFunScope>>()),
privateFunctions(std::make_shared<std::map<std::wstring,SharedFunScope>>()),
publicClasses(std::make_shared<std::map<std::wstring,SharedClassScope>>()),
privateClasses(std::make_shared<std::map<std::wstring,SharedClassScope>>()),
publicVariables(std::make_shared<std::map<std::wstring,SharedVariable>>()),
privateVariables(std::make_shared<std::map<std::wstring,SharedVariable>>())
{}

SharedMap<std::wstring,SharedFunScope> FileScope::getPublicFunctions() const {
    return publicFunctions;
}

SharedMap<std::wstring,SharedFunScope> FileScope::getPrivateFunctions() const {
    return privateFunctions;
}

SharedClassScope FileScope::getClassByType(SharedType type){
    auto classIterator=privateClasses->find(*type->getName());

    if(classIterator!=privateClasses->end())
        return classIterator->second;
    
    return parentScope->getClassByType(type);
}

SharedMap<std::wstring,SharedClassScope> FileScope::getPublicClasses() const {
    return publicClasses;
}

SharedMap<std::wstring,SharedClassScope> FileScope::getPrivateClasses() const {
    return privateClasses;
}

SharedFunScope FileScope::findPublicFunction(std::wstring decl){
    auto funIterator=publicFunctions->find(decl);

    if(funIterator!=publicFunctions->end())
        return funIterator->second;
    
    throw FunctionNotFoundException(decl);
}

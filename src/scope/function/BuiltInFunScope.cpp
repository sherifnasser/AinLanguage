#include "BuiltInFunScope.hpp"
#include "FunParam.hpp"
#include "PackageScope.hpp"
#include "FunDecl.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>
#include <string>
#include <vector>

BuiltInFunScope::BuiltInFunScope(
                     std::wstring name,
                     SharedType returnType,
                     std::map<std::wstring, SharedType> params
                 )
    : FunScope(
        PackageScope::AIN_PACKAGE,
        std::make_shared<FunDecl>(
            std::make_shared<std::wstring>(name),
            returnType,
            std::make_shared<bool>(false),
            std::make_shared<std::vector<SharedFunParam>>()
        )
    )
{
    for(auto paramsIterator:params){
        decl->params->push_back(
            std::make_shared<FunParam>(
                std::make_shared<std::wstring>(paramsIterator.first),
                paramsIterator.second
            )
        );
    }
}

BuiltInFunScope::~BuiltInFunScope()
{
    
}

#pragma once
#include "FunScope.hpp"
#include "SharedPtrTypes.hpp"
#include <map>
#include <string>
class BuiltInFunScope:public FunScope{
    public:
        BuiltInFunScope(
            std::wstring name,
            SharedType returnType,
            std::map<std::wstring, SharedType> params
        );
        ~BuiltInFunScope();
};
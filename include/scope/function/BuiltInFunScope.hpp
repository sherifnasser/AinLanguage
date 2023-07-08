#pragma once
#include "FunScope.hpp"
#include "SharedPtrTypes.hpp"
#include <functional>
#include <map>
#include <memory>
#include <string>
class BuiltInFunScope:public FunScope{
    private:
        std::function<SharedIValue(SharedMap<std::wstring, SharedIValue>)> invokeFun;
        static std::function<SharedIValue(SharedMap<std::wstring, SharedIValue>)> PRINT_INVOKE_FUN;
        static std::function<SharedIValue(SharedMap<std::wstring, SharedIValue>)> PRINTLN_INVOKE_FUN;

    public:
        BuiltInFunScope(
            std::wstring name,
            SharedType returnType,
            std::map<std::wstring, SharedType> params,
            std::function<SharedIValue(SharedMap<std::wstring, SharedIValue>)> invokeFun
        );
        ~BuiltInFunScope();
        
        SharedIValue invoke(SharedMap<std::wstring, SharedIValue> params) override;

        static void addBuiltInFunctionsTo(SharedFileScope fileScope);
};
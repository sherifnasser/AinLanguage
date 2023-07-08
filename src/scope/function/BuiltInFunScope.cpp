#include "BuiltInFunScope.hpp"
#include "FunParam.hpp"
#include "PackageScope.hpp"
#include "FunDecl.hpp"
#include "SharedPtrTypes.hpp"
#include "StringValue.hpp"
#include "Type.hpp"
#include "UnitValue.hpp"
#include "ainio.hpp"
#include "FileScope.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

BuiltInFunScope::BuiltInFunScope(
    std::wstring name,
    SharedType returnType,
    std::map<std::wstring, SharedType> params,
    std::function<SharedIValue(SharedMap<std::wstring, SharedIValue>)> invokeFun
):
    FunScope(
        PackageScope::AIN_PACKAGE,
        std::make_shared<FunDecl>(
                std::make_shared<std::wstring>(name),
                returnType,
                std::make_shared<bool>(false),
                std::make_shared<std::vector<SharedFunParam>>()
        )
    ),
    invokeFun(invokeFun)
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

SharedIValue BuiltInFunScope::invoke(SharedMap<std::wstring, SharedIValue> params) {
    return invokeFun(params);
}

void BuiltInFunScope::addBuiltInFunctionsTo(SharedFileScope fileScope){

    std::wstring READ_LINE_NAME=L"أدخل_";
    std::wstring READ_NAME=L"أدخل";
    std::wstring PRINT_NAME=L"اظهر";
    std::wstring PRINTLN_NAME=L"اظهر_";

    auto READ=std::make_shared<BuiltInFunScope>(
        READ_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{},
        [](SharedMap<std::wstring, SharedIValue>){
            auto input=ainread(false);
            return std::make_shared<StringValue>(input);
        }
    );

    auto READ_LINE=std::make_shared<BuiltInFunScope>(
        READ_LINE_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{},
        [](SharedMap<std::wstring, SharedIValue>){
            auto input=ainread(true);
            return std::make_shared<StringValue>(input);
        }
    );

    auto PRINT_INVOKE_FUN=
    [](SharedMap<std::wstring, SharedIValue> params){
        for(auto paramIterator:*params){
            auto paramVal=paramIterator.second->toString();
            ainprint(paramVal, false);
        }
        return std::make_shared<UnitValue>();
    };

    auto PRINTLN_INVOKE_FUN=
    [](SharedMap<std::wstring, SharedIValue> params){
        for(auto paramIterator:*params){
            auto paramVal=paramIterator.second->toString();
            ainprint(paramVal, true);
        }
        return std::make_shared<UnitValue>();
    };

    auto PRINT_INT=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_صحيح",Type::INT}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_INT=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_صحيح",Type::INT}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_UINT=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_صحيح_م",Type::UINT}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_UINT=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_صحيح_م",Type::UINT}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_LONG=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_كبير",Type::LONG}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_LONG=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_كبير",Type::LONG}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_ULONG=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_كبير_م",Type::ULONG}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_ULONG=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_كبير_م",Type::ULONG}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_FLOAT=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_عشري",Type::FLOAT}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_FLOAT=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_عشري",Type::FLOAT}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_DOUBLE=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_عشري_م",Type::DOUBLE}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_DOUBLE=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"رقم_عشري_م",Type::DOUBLE}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_CHAR=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"_حرف",Type::CHAR}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_CHAR=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"_حرف",Type::CHAR}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_STRING=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"_نص",Type::STRING}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_STRING=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"_نص",Type::STRING}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_BOOL=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"_منطقي",Type::BOOL}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_BOOL=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"_منطقي",Type::BOOL}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_UNIT=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"_الوحدة",Type::UNIT}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_UNIT=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{L"_الوحدة",Type::UNIT}},
        PRINTLN_INVOKE_FUN
    );


    auto builtInFunctions={
        READ,READ_LINE,
        PRINT_INT,PRINTLN_INT,
        PRINT_UINT,PRINTLN_UINT,
        PRINT_LONG,PRINTLN_LONG,
        PRINT_ULONG,PRINTLN_ULONG,
        PRINT_FLOAT,PRINTLN_FLOAT,
        PRINT_DOUBLE,PRINTLN_DOUBLE,
        PRINT_CHAR,PRINTLN_CHAR,
        PRINT_STRING,PRINTLN_STRING,
        PRINT_BOOL,PRINTLN_BOOL,
        PRINT_UNIT,PRINTLN_UNIT,
    };
    auto privateFunctions=fileScope->getPrivateFunctions();
    for(auto builtInFun:builtInFunctions){
        (*privateFunctions)[builtInFun->getDecl()->toString()]=builtInFun;
    }
}

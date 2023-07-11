#include "BuiltInFunScope.hpp"
#include "CharValue.hpp"
#include "DoubleClassScope.hpp"
#include "DoubleValue.hpp"
#include "FloatClassScope.hpp"
#include "FloatValue.hpp"
#include "FunParam.hpp"
#include "IntClassScope.hpp"
#include "IntValue.hpp"
#include "LongClassScope.hpp"
#include "LongValue.hpp"
#include "OperatorFunctions.hpp"
#include "PackageScope.hpp"
#include "FunDecl.hpp"
#include "SharedPtrTypes.hpp"
#include "StringValue.hpp"
#include "Type.hpp"
#include "UIntClassScope.hpp"
#include "UIntValue.hpp"
#include "ULongClassScope.hpp"
#include "ULongValue.hpp"
#include "UnitValue.hpp"
#include "ainio.hpp"
#include "FileScope.hpp"
#include "wchar_t_helper.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

BuiltInFunScope::BuiltInFunScope(
    std::wstring name,
    SharedType returnType,
    std::map<std::wstring, SharedType> params,
    std::function<SharedIValue(SharedMap<std::wstring, SharedIValue>)> invokeFun,
    bool isOperator
):
    FunScope(
        PackageScope::AIN_PACKAGE,
        std::make_shared<FunDecl>(
                std::make_shared<std::wstring>(name),
                returnType,
                std::make_shared<bool>(isOperator),
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
        std::map<std::wstring, SharedType>{{INT_PARAM_NAME,Type::INT}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_INT=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{INT_PARAM_NAME,Type::INT}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_UINT=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{UINT_PARAM_NAME,Type::UINT}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_UINT=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{UINT_PARAM_NAME,Type::UINT}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_LONG=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{LONG_PARAM_NAME,Type::LONG}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_LONG=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{LONG_PARAM_NAME,Type::LONG}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_ULONG=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{ULONG_PARAM_NAME,Type::ULONG}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_ULONG=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{ULONG_PARAM_NAME,Type::ULONG}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_FLOAT=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{FLOAT_PARAM_NAME,Type::FLOAT}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_FLOAT=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{FLOAT_PARAM_NAME,Type::FLOAT}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_DOUBLE=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{DOUBLE_PARAM_NAME,Type::DOUBLE}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_DOUBLE=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{DOUBLE_PARAM_NAME,Type::DOUBLE}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_CHAR=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{CHAR_PARAM_NAME,Type::CHAR}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_CHAR=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{CHAR_PARAM_NAME,Type::CHAR}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_STRING=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{STRING_PARAM_NAME,Type::STRING}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_STRING=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{STRING_PARAM_NAME,Type::STRING}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_BOOL=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{BOOL_PARAM_NAME,Type::BOOL}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_BOOL=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{BOOL_PARAM_NAME,Type::BOOL}},
        PRINTLN_INVOKE_FUN
    );

    auto PRINT_UNIT=std::make_shared<BuiltInFunScope>(
        PRINT_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{UNIT_PARAM_NAME,Type::UNIT}},
        PRINT_INVOKE_FUN
    );

    auto PRINTLN_UNIT=std::make_shared<BuiltInFunScope>(
        PRINTLN_NAME,
        Type::UNIT,
        std::map<std::wstring, SharedType>{{UNIT_PARAM_NAME,Type::UNIT}},
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

void BuiltInFunScope::addBuiltInFunctionsToBuiltInClasses() {
    addBuiltInFunctionsToIntClass();
    addBuiltInFunctionsToUIntClass();
    addBuiltInFunctionsToLongClass();
    addBuiltInFunctionsToULongClass();
    addBuiltInFunctionsToFloatClass();
    addBuiltInFunctionsToDoubleClass();
    addBuiltInFunctionsToBoolClass();
    addBuiltInFunctionsToCharClass();
    addBuiltInFunctionsToStringClass();
    addBuiltInFunctionsToUnitClass();
}

void BuiltInFunScope::addBuiltInFunctionsToIntClass(){

    auto classScope=std::dynamic_pointer_cast<IntClassScope>(Type::INT->getClassScope());
    
    using PrimitiveType=int;

    auto PLUS_INT=getPLusFun<PrimitiveType, IntValue, IntValue>(
        classScope,
        Type::INT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto PLUS_LONG=getPLusFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto PLUS_FLOAT=getPLusFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto PLUS_DOUBLE=getPLusFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto MINUS_INT=getMinusFun<PrimitiveType, IntValue, IntValue>(
        classScope,
        Type::INT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto MINUS_LONG=getMinusFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto MINUS_FLOAT=getMinusFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto MINUS_DOUBLE=getMinusFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto TIMES_INT=getTimesFun<PrimitiveType, IntValue, IntValue>(
        classScope,
        Type::INT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto TIMES_LONG=getTimesFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto TIMES_FLOAT=getTimesFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto TIMES_DOUBLE=getTimesFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto DIV_INT=getDivFun<PrimitiveType, IntValue, IntValue>(
        classScope,
        Type::INT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto DIV_LONG=getDivFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto DIV_FLOAT=getDivFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto DIV_DOUBLE=getDivFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto MOD_INT=getModFun<PrimitiveType, IntValue, IntValue>(
        classScope,
        Type::INT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto MOD_LONG=getModFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto TO_INT=getToIntFun<PrimitiveType>(classScope);

    auto TO_UINT=getToUIntFun<PrimitiveType>(classScope);

    auto TO_LONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_ULONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_FLOAT=getToFloatFun<PrimitiveType>(classScope);

    auto TO_DOUBLE=getToDoubleFun<PrimitiveType>(classScope);

    auto TO_STRING=getToStringFun<PrimitiveType>(classScope);

    auto TO_CHAR=std::make_shared<BuiltInFunScope>(
        TO_CHAR_NAME,
        Type::CHAR,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            wchar_t charValue=static_cast<wchar_t>(val);
            if(isKufrOrUnsupportedCharacter(charValue))
                throw; // TODO
            return std::make_shared<CharValue>(charValue);
        },
        true
    );


    auto funs={
        PLUS_INT,PLUS_LONG,PLUS_FLOAT,PLUS_DOUBLE,
        MINUS_INT,MINUS_LONG,MINUS_FLOAT,MINUS_DOUBLE,
        TIMES_INT,TIMES_LONG,TIMES_FLOAT,TIMES_DOUBLE,
        DIV_INT,DIV_LONG,DIV_FLOAT,DIV_DOUBLE,
        MOD_INT,MOD_LONG,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING,TO_CHAR
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToUIntClass(){

    auto classScope=std::dynamic_pointer_cast<UIntClassScope>(Type::UINT->getClassScope());
    
    using PrimitiveType=unsigned int;

    auto PLUS_UINT=getPLusFun<PrimitiveType, UIntValue, UIntValue>(
        classScope,
        Type::UINT,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto PLUS_ULONG=getPLusFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto MINUS_UINT=getMinusFun<PrimitiveType, UIntValue, UIntValue>(
        classScope,
        Type::UINT,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto MINUS_ULONG=getMinusFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto TIMES_UINT=getTimesFun<PrimitiveType, UIntValue, UIntValue>(
        classScope,
        Type::UINT,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto TIMES_ULONG=getTimesFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto DIV_UINT=getDivFun<PrimitiveType, UIntValue, UIntValue>(
        classScope,
        Type::UINT,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto DIV_ULONG=getDivFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto MOD_UINT=getModFun<PrimitiveType, UIntValue, UIntValue>(
        classScope,
        Type::UINT,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto MOD_ULONG=getModFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto TO_INT=getToIntFun<PrimitiveType>(classScope);

    auto TO_UINT=getToUIntFun<PrimitiveType>(classScope);

    auto TO_LONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_ULONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_FLOAT=getToFloatFun<PrimitiveType>(classScope);

    auto TO_DOUBLE=getToDoubleFun<PrimitiveType>(classScope);

    auto TO_STRING=getToStringFun<PrimitiveType>(classScope);

    auto funs={
        PLUS_UINT,PLUS_ULONG,
        MINUS_UINT,MINUS_ULONG,
        TIMES_UINT,TIMES_ULONG,
        DIV_UINT,DIV_ULONG,
        MOD_UINT,MOD_ULONG,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToLongClass(){

    auto classScope=std::dynamic_pointer_cast<LongClassScope>(Type::LONG->getClassScope());
    
    using PrimitiveType=long long;

    auto PLUS_INT=getPLusFun<PrimitiveType, IntValue, LongValue>(
        classScope,
        Type::LONG,
        INT_PARAM_NAME,
        Type::INT
    );

    auto PLUS_LONG=getPLusFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto PLUS_FLOAT=getPLusFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto PLUS_DOUBLE=getPLusFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto MINUS_INT=getMinusFun<PrimitiveType, IntValue, LongValue>(
        classScope,
        Type::LONG,
        INT_PARAM_NAME,
        Type::INT
    );

    auto MINUS_LONG=getMinusFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto MINUS_FLOAT=getMinusFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto MINUS_DOUBLE=getMinusFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto TIMES_INT=getTimesFun<PrimitiveType, IntValue, LongValue>(
        classScope,
        Type::LONG,
        INT_PARAM_NAME,
        Type::INT
    );

    auto TIMES_LONG=getTimesFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto TIMES_FLOAT=getTimesFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto TIMES_DOUBLE=getTimesFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto DIV_INT=getDivFun<PrimitiveType, IntValue, LongValue>(
        classScope,
        Type::LONG,
        INT_PARAM_NAME,
        Type::INT
    );

    auto DIV_LONG=getDivFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto DIV_FLOAT=getDivFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto DIV_DOUBLE=getDivFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto MOD_INT=getModFun<PrimitiveType, IntValue, LongValue>(
        classScope,
        Type::LONG,
        INT_PARAM_NAME,
        Type::INT
    );

    auto MOD_LONG=getModFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto TO_INT=getToIntFun<PrimitiveType>(classScope);

    auto TO_UINT=getToUIntFun<PrimitiveType>(classScope);

    auto TO_LONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_ULONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_FLOAT=getToFloatFun<PrimitiveType>(classScope);

    auto TO_DOUBLE=getToDoubleFun<PrimitiveType>(classScope);

    auto TO_STRING=getToStringFun<PrimitiveType>(classScope);

    auto funs={
        PLUS_INT,PLUS_LONG,PLUS_FLOAT,PLUS_DOUBLE,
        MINUS_INT,MINUS_LONG,MINUS_FLOAT,MINUS_DOUBLE,
        TIMES_INT,TIMES_LONG,TIMES_FLOAT,TIMES_DOUBLE,
        DIV_INT,DIV_LONG,DIV_FLOAT,DIV_DOUBLE,
        MOD_INT,MOD_LONG,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToULongClass(){

    auto classScope=std::dynamic_pointer_cast<ULongClassScope>(Type::ULONG->getClassScope());
    
    using PrimitiveType=unsigned long long;

    auto PLUS_UINT=getPLusFun<PrimitiveType, UIntValue, ULongValue>(
        classScope,
        Type::ULONG,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto PLUS_ULONG=getPLusFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto MINUS_UINT=getMinusFun<PrimitiveType, UIntValue, ULongValue>(
        classScope,
        Type::ULONG,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto MINUS_ULONG=getMinusFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto TIMES_UINT=getTimesFun<PrimitiveType, UIntValue, ULongValue>(
        classScope,
        Type::ULONG,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto TIMES_ULONG=getTimesFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto DIV_UINT=getDivFun<PrimitiveType, UIntValue, ULongValue>(
        classScope,
        Type::ULONG,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto DIV_ULONG=getDivFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto MOD_UINT=getModFun<PrimitiveType, UIntValue, ULongValue>(
        classScope,
        Type::ULONG,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto MOD_ULONG=getModFun<PrimitiveType, ULongValue, ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto TO_INT=getToIntFun<PrimitiveType>(classScope);

    auto TO_UINT=getToUIntFun<PrimitiveType>(classScope);

    auto TO_LONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_ULONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_FLOAT=getToFloatFun<PrimitiveType>(classScope);

    auto TO_DOUBLE=getToDoubleFun<PrimitiveType>(classScope);

    auto TO_STRING=getToStringFun<PrimitiveType>(classScope);

    auto funs={
        PLUS_UINT,PLUS_ULONG,
        MINUS_UINT,MINUS_ULONG,
        TIMES_UINT,TIMES_ULONG,
        DIV_UINT,DIV_ULONG,
        MOD_UINT,MOD_ULONG,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToFloatClass(){

    auto classScope=std::dynamic_pointer_cast<FloatClassScope>(Type::FLOAT->getClassScope());
    
    using PrimitiveType=float;

    auto PLUS_INT=getPLusFun<PrimitiveType, IntValue, FloatValue>(
        classScope,
        Type::FLOAT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto PLUS_LONG=getPLusFun<PrimitiveType, LongValue, FloatValue>(
        classScope,
        Type::FLOAT,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto PLUS_FLOAT=getPLusFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto PLUS_DOUBLE=getPLusFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto MINUS_INT=getMinusFun<PrimitiveType, IntValue, FloatValue>(
        classScope,
        Type::FLOAT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto MINUS_LONG=getMinusFun<PrimitiveType, LongValue, FloatValue>(
        classScope,
        Type::FLOAT,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto MINUS_FLOAT=getMinusFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto MINUS_DOUBLE=getMinusFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto TIMES_INT=getTimesFun<PrimitiveType, IntValue, FloatValue>(
        classScope,
        Type::FLOAT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto TIMES_LONG=getTimesFun<PrimitiveType, LongValue, FloatValue>(
        classScope,
        Type::FLOAT,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto TIMES_FLOAT=getTimesFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto TIMES_DOUBLE=getTimesFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto DIV_INT=getDivFun<PrimitiveType, IntValue, FloatValue>(
        classScope,
        Type::FLOAT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto DIV_LONG=getDivFun<PrimitiveType, LongValue, FloatValue>(
        classScope,
        Type::FLOAT,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto DIV_FLOAT=getDivFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto DIV_DOUBLE=getDivFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto TO_INT=getToIntFun<PrimitiveType>(classScope);

    auto TO_UINT=getToUIntFun<PrimitiveType>(classScope);

    auto TO_LONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_ULONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_FLOAT=getToFloatFun<PrimitiveType>(classScope);

    auto TO_DOUBLE=getToDoubleFun<PrimitiveType>(classScope);

    auto TO_STRING=getToStringFun<PrimitiveType>(classScope);

    auto funs={
        PLUS_INT,PLUS_LONG,PLUS_FLOAT,PLUS_DOUBLE,
        MINUS_INT,MINUS_LONG,MINUS_FLOAT,MINUS_DOUBLE,
        TIMES_INT,TIMES_LONG,TIMES_FLOAT,TIMES_DOUBLE,
        DIV_INT,DIV_LONG,DIV_FLOAT,DIV_DOUBLE,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToDoubleClass(){

    auto classScope=std::dynamic_pointer_cast<DoubleClassScope>(Type::DOUBLE->getClassScope());
    
    using PrimitiveType=long double;

    auto PLUS_INT=getPLusFun<PrimitiveType, IntValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        INT_PARAM_NAME,
        Type::INT
    );

    auto PLUS_LONG=getPLusFun<PrimitiveType, LongValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto PLUS_FLOAT=getPLusFun<PrimitiveType, FloatValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto PLUS_DOUBLE=getPLusFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto MINUS_INT=getMinusFun<PrimitiveType, IntValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        INT_PARAM_NAME,
        Type::INT
    );

    auto MINUS_LONG=getMinusFun<PrimitiveType, LongValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto MINUS_FLOAT=getMinusFun<PrimitiveType, FloatValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto MINUS_DOUBLE=getMinusFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto TIMES_INT=getTimesFun<PrimitiveType, IntValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        INT_PARAM_NAME,
        Type::INT
    );

    auto TIMES_LONG=getTimesFun<PrimitiveType, LongValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto TIMES_FLOAT=getTimesFun<PrimitiveType, FloatValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto TIMES_DOUBLE=getTimesFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto DIV_INT=getDivFun<PrimitiveType, IntValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        INT_PARAM_NAME,
        Type::INT
    );

    auto DIV_LONG=getDivFun<PrimitiveType, LongValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto DIV_FLOAT=getDivFun<PrimitiveType, FloatValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto DIV_DOUBLE=getDivFun<PrimitiveType, DoubleValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto TO_INT=getToIntFun<PrimitiveType>(classScope);

    auto TO_UINT=getToUIntFun<PrimitiveType>(classScope);

    auto TO_LONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_ULONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_FLOAT=getToFloatFun<PrimitiveType>(classScope);

    auto TO_DOUBLE=getToDoubleFun<PrimitiveType>(classScope);

    auto TO_STRING=getToStringFun<PrimitiveType>(classScope);

    auto funs={
        PLUS_INT,PLUS_LONG,PLUS_FLOAT,PLUS_DOUBLE,
        MINUS_INT,MINUS_LONG,MINUS_FLOAT,MINUS_DOUBLE,
        TIMES_INT,TIMES_LONG,TIMES_FLOAT,TIMES_DOUBLE,
        DIV_INT,DIV_LONG,DIV_FLOAT,DIV_DOUBLE,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToBoolClass() {
    
}

void BuiltInFunScope::addBuiltInFunctionsToCharClass() {
    
}

void BuiltInFunScope::addBuiltInFunctionsToStringClass() {
    
}

void BuiltInFunScope::addBuiltInFunctionsToUnitClass() {
    
}

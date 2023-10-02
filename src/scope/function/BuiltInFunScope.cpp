#include "BuiltInFunScope.hpp"
#include "BoolClassScope.hpp"
#include "BoolValue.hpp"
#include "CharClassScope.hpp"
#include "CharValue.hpp"
#include "DoubleClassScope.hpp"
#include "DoubleValue.hpp"
#include "FloatClassScope.hpp"
#include "FloatValue.hpp"
#include "FunParam.hpp"
#include "IntClassScope.hpp"
#include "IntValue.hpp"
#include "KeywordToken.hpp"
#include "LongClassScope.hpp"
#include "LongValue.hpp"
#include "OperatorFunctions.hpp"
#include "PackageScope.hpp"
#include "FunDecl.hpp"
#include "SharedPtrTypes.hpp"
#include "StringClassScope.hpp"
#include "StringValue.hpp"
#include "Type.hpp"
#include "UIntClassScope.hpp"
#include "UIntValue.hpp"
#include "ULongClassScope.hpp"
#include "ULongValue.hpp"
#include "UnitValue.hpp"
#include "ainio.hpp"
#include "FileScope.hpp"
#include "runtime/NumberFormatException.hpp"
#include "wchar_t_helper.hpp"
#include <exception>
#include <limits>
#include <map>
#include <memory>
#include <stdexcept>
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

    auto PLUS_INT=getPlusFun<PrimitiveType, IntValue, IntValue>(
        classScope,
        Type::INT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto PLUS_LONG=getPlusFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto PLUS_FLOAT=getPlusFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto PLUS_DOUBLE=getPlusFun<PrimitiveType, DoubleValue, DoubleValue>(
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

    auto COMPARE_TO_INT=getCompareToFun<PrimitiveType, IntValue>(
        classScope,
        INT_PARAM_NAME,
        Type::INT
    );

    auto COMPARE_TO_LONG=getCompareToFun<PrimitiveType, LongValue>(
        classScope,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto COMPARE_TO_FLOAT=getCompareToFun<PrimitiveType, FloatValue>(
        classScope,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto COMPARE_TO_DOUBLE=getCompareToFun<PrimitiveType, DoubleValue>(
        classScope,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto EQUALS=getEqualsFun<PrimitiveType>(
        classScope,
        INT_PARAM_NAME,
        Type::INT
    );

    auto UNARY_PLUS=getUnaryPlusFun<PrimitiveType,IntValue>(classScope,Type::INT);

    auto UNARY_MINUS=getUnaryMinusFun<PrimitiveType,IntValue>(classScope,Type::INT);

    auto INC=getIncFun<PrimitiveType,IntValue>(classScope,Type::INT);

    auto DEC=getDecFun<PrimitiveType,IntValue>(classScope,Type::INT);

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

    auto SHR=getShrFun<PrimitiveType,IntValue>(classScope,Type::INT);

    auto SHL=getShlFun<PrimitiveType,IntValue>(classScope,Type::INT);

    auto BIT_AND=getBitAndFun<PrimitiveType,IntValue>(
        classScope,
        Type::INT,
        INT_PARAM_NAME
    );

    auto XOR=getXorFun<PrimitiveType,IntValue>(
        classScope,
        Type::INT,
        INT_PARAM_NAME
    );

    auto BIT_OR=getBitOrFun<PrimitiveType,IntValue>(
        classScope,
        Type::INT,
        INT_PARAM_NAME
    );

    auto BIT_NOT=getBitNotFun<PrimitiveType,IntValue>(
        classScope,
        Type::INT
    );

    auto funs={
        PLUS_INT,PLUS_LONG,PLUS_FLOAT,PLUS_DOUBLE,
        MINUS_INT,MINUS_LONG,MINUS_FLOAT,MINUS_DOUBLE,
        TIMES_INT,TIMES_LONG,TIMES_FLOAT,TIMES_DOUBLE,
        DIV_INT,DIV_LONG,DIV_FLOAT,DIV_DOUBLE,
        MOD_INT,MOD_LONG,
        COMPARE_TO_INT,COMPARE_TO_LONG,COMPARE_TO_FLOAT,COMPARE_TO_DOUBLE,
        EQUALS,
        UNARY_PLUS,UNARY_MINUS,
        INC,DEC,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING,TO_CHAR,
        SHR,SHL,BIT_AND,XOR,BIT_OR,BIT_NOT
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToUIntClass(){

    auto classScope=std::dynamic_pointer_cast<UIntClassScope>(Type::UINT->getClassScope());
    
    using PrimitiveType=unsigned int;

    auto PLUS_UINT=getPlusFun<PrimitiveType, UIntValue, UIntValue>(
        classScope,
        Type::UINT,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto PLUS_ULONG=getPlusFun<PrimitiveType, ULongValue, ULongValue>(
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

    auto COMPARE_TO_UINT=getCompareToFun<PrimitiveType, UIntValue>(
        classScope,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto COMPARE_TO_ULONG=getCompareToFun<PrimitiveType, ULongValue>(
        classScope,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto EQUALS=getEqualsFun<PrimitiveType>(
        classScope,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto INC=getIncFun<PrimitiveType,UIntValue>(classScope,Type::UINT);

    auto DEC=getDecFun<PrimitiveType,UIntValue>(classScope,Type::UINT);

    auto TO_INT=getToIntFun<PrimitiveType>(classScope);

    auto TO_UINT=getToUIntFun<PrimitiveType>(classScope);

    auto TO_LONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_ULONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_FLOAT=getToFloatFun<PrimitiveType>(classScope);

    auto TO_DOUBLE=getToDoubleFun<PrimitiveType>(classScope);

    auto TO_STRING=getToStringFun<PrimitiveType>(classScope);

    auto SHR=getShrFun<PrimitiveType,UIntValue>(classScope,Type::UINT);

    auto SHL=getShlFun<PrimitiveType,UIntValue>(classScope,Type::UINT);

    auto BIT_AND=getBitAndFun<PrimitiveType,UIntValue>(
        classScope,
        Type::UINT,
        UINT_PARAM_NAME
    );

    auto XOR=getXorFun<PrimitiveType,UIntValue>(
        classScope,
        Type::UINT,
        UINT_PARAM_NAME
    );

    auto BIT_OR=getBitOrFun<PrimitiveType,UIntValue>(
        classScope,
        Type::UINT,
        UINT_PARAM_NAME
    );

    auto BIT_NOT=getBitNotFun<PrimitiveType,UIntValue>(
        classScope,
        Type::UINT
    );

    auto funs={
        PLUS_UINT,PLUS_ULONG,
        MINUS_UINT,MINUS_ULONG,
        TIMES_UINT,TIMES_ULONG,
        DIV_UINT,DIV_ULONG,
        MOD_UINT,MOD_ULONG,
        COMPARE_TO_UINT,COMPARE_TO_ULONG,
        EQUALS,
        INC,DEC,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING,
        SHR,SHL,BIT_AND,XOR,BIT_OR,BIT_NOT
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToLongClass(){

    auto classScope=std::dynamic_pointer_cast<LongClassScope>(Type::LONG->getClassScope());
    
    using PrimitiveType=long long;

    auto PLUS_INT=getPlusFun<PrimitiveType, IntValue, LongValue>(
        classScope,
        Type::LONG,
        INT_PARAM_NAME,
        Type::INT
    );

    auto PLUS_LONG=getPlusFun<PrimitiveType, LongValue, LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto PLUS_FLOAT=getPlusFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto PLUS_DOUBLE=getPlusFun<PrimitiveType, DoubleValue, DoubleValue>(
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

    auto COMPARE_TO_INT=getCompareToFun<PrimitiveType, IntValue>(
        classScope,
        INT_PARAM_NAME,
        Type::INT
    );

    auto COMPARE_TO_LONG=getCompareToFun<PrimitiveType, LongValue>(
        classScope,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto COMPARE_TO_FLOAT=getCompareToFun<PrimitiveType, FloatValue>(
        classScope,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto COMPARE_TO_DOUBLE=getCompareToFun<PrimitiveType, DoubleValue>(
        classScope,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto EQUALS=getEqualsFun<PrimitiveType>(
        classScope,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto UNARY_PLUS=getUnaryPlusFun<PrimitiveType,LongValue>(classScope,Type::LONG);

    auto UNARY_MINUS=getUnaryMinusFun<PrimitiveType,LongValue>(classScope,Type::LONG);

    auto INC=getIncFun<PrimitiveType,LongValue>(classScope,Type::LONG);

    auto DEC=getDecFun<PrimitiveType,LongValue>(classScope,Type::LONG);

    auto TO_INT=getToIntFun<PrimitiveType>(classScope);

    auto TO_UINT=getToUIntFun<PrimitiveType>(classScope);

    auto TO_LONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_ULONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_FLOAT=getToFloatFun<PrimitiveType>(classScope);

    auto TO_DOUBLE=getToDoubleFun<PrimitiveType>(classScope);

    auto TO_STRING=getToStringFun<PrimitiveType>(classScope);

    auto SHR=getShrFun<PrimitiveType,LongValue>(classScope,Type::LONG);

    auto SHL=getShlFun<PrimitiveType,LongValue>(classScope,Type::LONG);

    auto BIT_AND=getBitAndFun<PrimitiveType,LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME
    );

    auto XOR=getXorFun<PrimitiveType,LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME
    );

    auto BIT_OR=getBitOrFun<PrimitiveType,LongValue>(
        classScope,
        Type::LONG,
        LONG_PARAM_NAME
    );

    auto BIT_NOT=getBitNotFun<PrimitiveType,LongValue>(
        classScope,
        Type::LONG
    );

    auto funs={
        PLUS_INT,PLUS_LONG,PLUS_FLOAT,PLUS_DOUBLE,
        MINUS_INT,MINUS_LONG,MINUS_FLOAT,MINUS_DOUBLE,
        TIMES_INT,TIMES_LONG,TIMES_FLOAT,TIMES_DOUBLE,
        DIV_INT,DIV_LONG,DIV_FLOAT,DIV_DOUBLE,
        MOD_INT,MOD_LONG,
        COMPARE_TO_INT,COMPARE_TO_LONG,COMPARE_TO_FLOAT,COMPARE_TO_DOUBLE,
        EQUALS,
        UNARY_PLUS,UNARY_MINUS,
        INC,DEC,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING,
        SHR,SHL,BIT_AND,XOR,BIT_OR,BIT_NOT
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToULongClass(){

    auto classScope=std::dynamic_pointer_cast<ULongClassScope>(Type::ULONG->getClassScope());
    
    using PrimitiveType=unsigned long long;

    auto PLUS_UINT=getPlusFun<PrimitiveType, UIntValue, ULongValue>(
        classScope,
        Type::ULONG,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto PLUS_ULONG=getPlusFun<PrimitiveType, ULongValue, ULongValue>(
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

    auto COMPARE_TO_UINT=getCompareToFun<PrimitiveType, UIntValue>(
        classScope,
        UINT_PARAM_NAME,
        Type::UINT
    );

    auto COMPARE_TO_ULONG=getCompareToFun<PrimitiveType, ULongValue>(
        classScope,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto EQUALS=getEqualsFun<PrimitiveType>(
        classScope,
        ULONG_PARAM_NAME,
        Type::ULONG
    );

    auto INC=getIncFun<PrimitiveType,ULongValue>(classScope,Type::ULONG);

    auto DEC=getDecFun<PrimitiveType,ULongValue>(classScope,Type::ULONG);

    auto TO_INT=getToIntFun<PrimitiveType>(classScope);

    auto TO_UINT=getToUIntFun<PrimitiveType>(classScope);

    auto TO_LONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_ULONG=getToUIntFun<PrimitiveType>(classScope);

    auto TO_FLOAT=getToFloatFun<PrimitiveType>(classScope);

    auto TO_DOUBLE=getToDoubleFun<PrimitiveType>(classScope);

    auto TO_STRING=getToStringFun<PrimitiveType>(classScope);

    auto SHR=getShrFun<PrimitiveType,ULongValue>(classScope,Type::ULONG);

    auto SHL=getShlFun<PrimitiveType,ULongValue>(classScope,Type::ULONG);

    auto BIT_AND=getBitAndFun<PrimitiveType,ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME
    );

    auto XOR=getXorFun<PrimitiveType,ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME
    );

    auto BIT_OR=getBitOrFun<PrimitiveType,ULongValue>(
        classScope,
        Type::ULONG,
        ULONG_PARAM_NAME
    );

    auto BIT_NOT=getBitNotFun<PrimitiveType,ULongValue>(
        classScope,
        Type::ULONG
    );

    auto funs={
        PLUS_UINT,PLUS_ULONG,
        MINUS_UINT,MINUS_ULONG,
        TIMES_UINT,TIMES_ULONG,
        DIV_UINT,DIV_ULONG,
        MOD_UINT,MOD_ULONG,
        COMPARE_TO_UINT,COMPARE_TO_ULONG,
        EQUALS,
        INC,DEC,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING,
        SHR,SHL,BIT_AND,XOR,BIT_OR,BIT_NOT
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToFloatClass(){

    auto classScope=std::dynamic_pointer_cast<FloatClassScope>(Type::FLOAT->getClassScope());
    
    using PrimitiveType=float;

    auto PLUS_INT=getPlusFun<PrimitiveType, IntValue, FloatValue>(
        classScope,
        Type::FLOAT,
        INT_PARAM_NAME,
        Type::INT
    );

    auto PLUS_LONG=getPlusFun<PrimitiveType, LongValue, FloatValue>(
        classScope,
        Type::FLOAT,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto PLUS_FLOAT=getPlusFun<PrimitiveType, FloatValue, FloatValue>(
        classScope,
        Type::FLOAT,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto PLUS_DOUBLE=getPlusFun<PrimitiveType, DoubleValue, DoubleValue>(
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

    auto COMPARE_TO_INT=getCompareToFun<PrimitiveType, IntValue>(
        classScope,
        INT_PARAM_NAME,
        Type::INT
    );

    auto COMPARE_TO_LONG=getCompareToFun<PrimitiveType, LongValue>(
        classScope,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto COMPARE_TO_FLOAT=getCompareToFun<PrimitiveType, FloatValue>(
        classScope,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto COMPARE_TO_DOUBLE=getCompareToFun<PrimitiveType, DoubleValue>(
        classScope,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto EQUALS=getEqualsFun<PrimitiveType>(
        classScope,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto UNARY_PLUS=getUnaryPlusFun<PrimitiveType,FloatValue>(classScope,Type::FLOAT);

    auto UNARY_MINUS=getUnaryMinusFun<PrimitiveType,FloatValue>(classScope,Type::FLOAT);

    auto INC=getIncFun<PrimitiveType,FloatValue>(classScope,Type::FLOAT);

    auto DEC=getDecFun<PrimitiveType,FloatValue>(classScope,Type::FLOAT);

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
        COMPARE_TO_INT,COMPARE_TO_LONG,COMPARE_TO_FLOAT,COMPARE_TO_DOUBLE,
        EQUALS,
        UNARY_PLUS,UNARY_MINUS,
        INC,DEC,
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

    auto PLUS_INT=getPlusFun<PrimitiveType, IntValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        INT_PARAM_NAME,
        Type::INT
    );

    auto PLUS_LONG=getPlusFun<PrimitiveType, LongValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto PLUS_FLOAT=getPlusFun<PrimitiveType, FloatValue, DoubleValue>(
        classScope,
        Type::DOUBLE,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto PLUS_DOUBLE=getPlusFun<PrimitiveType, DoubleValue, DoubleValue>(
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

    auto COMPARE_TO_INT=getCompareToFun<PrimitiveType, IntValue>(
        classScope,
        INT_PARAM_NAME,
        Type::INT
    );

    auto COMPARE_TO_LONG=getCompareToFun<PrimitiveType, LongValue>(
        classScope,
        LONG_PARAM_NAME,
        Type::LONG
    );

    auto COMPARE_TO_FLOAT=getCompareToFun<PrimitiveType, FloatValue>(
        classScope,
        FLOAT_PARAM_NAME,
        Type::FLOAT
    );

    auto COMPARE_TO_DOUBLE=getCompareToFun<PrimitiveType, DoubleValue>(
        classScope,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto EQUALS=getEqualsFun<PrimitiveType>(
        classScope,
        DOUBLE_PARAM_NAME,
        Type::DOUBLE
    );

    auto UNARY_PLUS=getUnaryPlusFun<PrimitiveType,DoubleValue>(classScope,Type::DOUBLE);

    auto UNARY_MINUS=getUnaryMinusFun<PrimitiveType,DoubleValue>(classScope,Type::DOUBLE);

    auto INC=getIncFun<PrimitiveType,DoubleValue>(classScope,Type::DOUBLE);

    auto DEC=getDecFun<PrimitiveType,DoubleValue>(classScope,Type::DOUBLE);

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
        COMPARE_TO_INT,COMPARE_TO_LONG,COMPARE_TO_FLOAT,COMPARE_TO_DOUBLE,
        EQUALS,
        UNARY_PLUS,UNARY_MINUS,
        INC,DEC,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,TO_STRING
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToBoolClass(){

    auto classScope=std::dynamic_pointer_cast<BoolClassScope>(Type::BOOL->getClassScope());
    
    using PrimitiveType=bool;

    auto NOT=std::make_shared<BuiltInFunScope>(
        OperatorFunctions::LOGICAL_NOT_NAME,
        Type::BOOL,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto value=classScope->getValue();
            return std::make_shared<BoolValue>(!value);
        },
        true
    );

    auto EQUALS=getEqualsFun<PrimitiveType>(
        classScope,
        BOOL_PARAM_NAME,
        Type::BOOL
    );

    auto TO_STRING=std::make_shared<BuiltInFunScope>(
        TO_STRING_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto value=classScope->getValue();
            return std::make_shared<StringValue>(
                (value)?KeywordToken::TRUE.getVal():KeywordToken::FALSE.getVal()
            );
        },
        true
    );

    auto BIT_AND=getBitAndFun<PrimitiveType,BoolValue>(
        classScope,
        Type::BOOL,
        BOOL_PARAM_NAME
    );

    auto XOR=getXorFun<PrimitiveType,BoolValue>(
        classScope,
        Type::BOOL,
        BOOL_PARAM_NAME
    );

    auto BIT_OR=getBitOrFun<PrimitiveType,BoolValue>(
        classScope,
        Type::BOOL,
        BOOL_PARAM_NAME
    );

    auto funs={
        NOT,
        EQUALS,
        TO_STRING,
        BIT_AND,XOR,BIT_OR,
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }
    
}

void BuiltInFunScope::addBuiltInFunctionsToCharClass() {
    
    auto classScope=std::dynamic_pointer_cast<CharClassScope>(Type::CHAR->getClassScope());
    
    using PrimitiveType=wchar_t;

    auto PLUS_INT=std::make_shared<BuiltInFunScope>(
        OperatorFunctions::PLUS_NAME,
        Type::CHAR,
        std::map<std::wstring, SharedType>{{INT_PARAM_NAME,Type::INT}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<IntValue>(params->at(INT_PARAM_NAME))->getValue();
            auto charValue=static_cast<wchar_t>(firstVal+secondVal);
            if(isKufrOrUnsupportedCharacter(charValue))
                throw; // TODO
            return std::make_shared<CharValue>(charValue);
        },
        true
    );

    auto PLUS_STRING=std::make_shared<BuiltInFunScope>(
        OperatorFunctions::PLUS_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{{STRING_PARAM_NAME,Type::STRING}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<StringValue>(params->at(STRING_PARAM_NAME))->getValue();
            std::wstring val=L"";
            val+=firstVal;
            val+=secondVal;
            return std::make_shared<StringValue>(val);
        },
        true
    );

    auto MINUS_INT=std::make_shared<BuiltInFunScope>(
        OperatorFunctions::MINUS_NAME,
        Type::CHAR,
        std::map<std::wstring, SharedType>{{INT_PARAM_NAME,Type::INT}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<IntValue>(params->at(INT_PARAM_NAME))->getValue();
            auto charValue=static_cast<wchar_t>(firstVal-secondVal);
            if(isKufrOrUnsupportedCharacter(charValue))
                throw; // TODO
            return std::make_shared<CharValue>(charValue);
        },
        true
    );

    auto MINUS_CHAR=getMinusFun<PrimitiveType, CharValue, IntValue>(
        classScope,
        Type::INT,
        CHAR_PARAM_NAME,
        Type::CHAR
    );

    auto COMPARE_TO_CHAR=getCompareToFun<PrimitiveType, CharValue>(
        classScope,
        CHAR_PARAM_NAME,
        Type::CHAR
    );

    auto EQUALS=getEqualsFun<PrimitiveType>(
        classScope,
        CHAR_PARAM_NAME,
        Type::CHAR
    );

    auto TO_CHAR=std::make_shared<BuiltInFunScope>(
        TO_CHAR_NAME,
        Type::CHAR,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            // no need to check for kufr or unsupported characters as this method cannot be called from those characters
            return std::make_shared<CharValue>(val);
        },
        true
    );

    auto TO_STRING=std::make_shared<BuiltInFunScope>(
        TO_STRING_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto value=classScope->getValue();
            std::wstring val=L"";
            val+=value;
            return std::make_shared<StringValue>(val);
        },
        true
    );

    auto funs={
        PLUS_INT,PLUS_STRING,
        MINUS_INT,MINUS_CHAR,
        COMPARE_TO_CHAR,
        EQUALS,
        TO_CHAR,TO_STRING
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToStringClass() {
        
    auto classScope=std::dynamic_pointer_cast<StringClassScope>(Type::STRING->getClassScope());

    auto PLUS_STRING=std::make_shared<BuiltInFunScope>(
        OperatorFunctions::PLUS_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{{STRING_PARAM_NAME,Type::STRING}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<StringValue>(params->at(STRING_PARAM_NAME))->getValue();
            std::wstring val=L"";
            val+=firstVal;
            val+=secondVal;
            return std::make_shared<StringValue>(val);
        },
        true
    );

    auto PLUS_CHAR=std::make_shared<BuiltInFunScope>(
        OperatorFunctions::PLUS_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{{CHAR_PARAM_NAME,Type::CHAR}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<CharValue>(params->at(CHAR_PARAM_NAME))->toString();
            std::wstring val=L"";
            val+=firstVal;
            val+=secondVal;
            return std::make_shared<StringValue>(val);
        },
        true
    );

    auto EQUALS=std::make_shared<BuiltInFunScope>(
        OperatorFunctions::EQUALS_NAME,
        Type::BOOL,
        std::map<std::wstring, SharedType>{{STRING_PARAM_NAME,Type::STRING}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<StringValue>(params->at(STRING_PARAM_NAME))->getValue();
            auto equalsVal=firstVal==secondVal;
            return std::make_shared<BoolValue>(equalsVal);
        },
        true
    );

    auto TO_INT=std::make_shared<BuiltInFunScope>(
        TO_INT_NAME,
        Type::INT,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            try{
                auto value=std::stoi(val);
                return std::make_shared<IntValue>(value);
            }catch(std::exception e){
                throw NumberFormatException(val);
            }
        },
        true
    );

    auto TO_UINT=std::make_shared<BuiltInFunScope>(
        TO_UINT_NAME,
        Type::UINT,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            try{
                auto value=std::stoull(val);

                if(value>std::numeric_limits<unsigned int>().max())
                    throw NumberFormatException(val);

                return std::make_shared<UIntValue>(value);
            }catch(std::exception e){
                throw NumberFormatException(val);
            }
        },
        true
    );

    auto TO_LONG=std::make_shared<BuiltInFunScope>(
        TO_LONG_NAME,
        Type::LONG,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            try{
                auto value=std::stoll(val);
                return std::make_shared<LongValue>(value);
            }catch(std::exception e){
                throw NumberFormatException(val);
            }
        },
        true
    );

    auto TO_ULONG=std::make_shared<BuiltInFunScope>(
        TO_ULONG_NAME,
        Type::ULONG,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            try{
                auto value=std::stoull(val);
                return std::make_shared<ULongValue>(value);
            }catch(std::exception e){
                throw NumberFormatException(val);
            }
        },
        true
    );

    auto TO_FLOAT=std::make_shared<BuiltInFunScope>(
        TO_FLOAT_NAME,
        Type::FLOAT,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            try{
                auto value=std::stof(val);
                return std::make_shared<FloatValue>(value);
            }catch(std::exception e){
                throw NumberFormatException(val);
            }
        },
        true
    );

    auto TO_DOUBLE=std::make_shared<BuiltInFunScope>(
        TO_DOUBLE_NAME,
        Type::DOUBLE,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            try{
                auto value=std::stold(val);
                return std::make_shared<DoubleValue>(value);
            }catch(std::exception e){
                throw NumberFormatException(val);
            }
        },
        true
    );

    auto TO_STRING=std::make_shared<BuiltInFunScope>(
        TO_STRING_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            return std::make_shared<StringValue>(val);
        },
        true
    );

    auto funs={
        PLUS_STRING,PLUS_CHAR,
        EQUALS,
        TO_INT,TO_UINT,TO_LONG,TO_ULONG,
        TO_FLOAT,TO_DOUBLE,
        TO_STRING
    };

    auto publicFuns=classScope->getPublicFunctions();
    for(auto fun:funs){
        (*publicFuns)[fun->getDecl()->toString()]=fun;
    }

}

void BuiltInFunScope::addBuiltInFunctionsToUnitClass(){

    auto TO_STRING=std::make_shared<BuiltInFunScope>(
        TO_STRING_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            return std::make_shared<StringValue>(*Type::UNIT->getName());
        },
        true
    );

    auto publicFuns=Type::UNIT->getClassScope()->getPublicFunctions();
   
    (*publicFuns)[TO_STRING->getDecl()->toString()]=TO_STRING;

}
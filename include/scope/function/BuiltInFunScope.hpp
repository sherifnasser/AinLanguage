#pragma once
#include "BoolValue.hpp"
#include "DoubleValue.hpp"
#include "FloatValue.hpp"
#include "FunScope.hpp"
#include "IntValue.hpp"
#include "LongValue.hpp"
#include "OperatorFunctions.hpp"
#include "PrimitiveClassScope.hpp"
#include "PrimitiveValue.hpp"
#include "SharedPtrTypes.hpp"
#include "StringValue.hpp"
#include "Type.hpp"
#include "UIntValue.hpp"
#include "ULongValue.hpp"
#include <functional>
#include <map>
#include <memory>
#include <string>
class BuiltInFunScope:public FunScope{
    private:
        std::function<SharedIValue(SharedMap<std::wstring, SharedIValue>)> invokeFun;
        static void addBuiltInFunctionsToIntClass();
        static void addBuiltInFunctionsToUIntClass();
        static void addBuiltInFunctionsToLongClass();
        static void addBuiltInFunctionsToULongClass();
        static void addBuiltInFunctionsToFloatClass();
        static void addBuiltInFunctionsToDoubleClass();
        static void addBuiltInFunctionsToBoolClass();
        static void addBuiltInFunctionsToCharClass();
        static void addBuiltInFunctionsToStringClass();
        static void addBuiltInFunctionsToUnitClass();
        void accept(ASTVisitor *visitor) override;

        template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getPlusFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType,
            std::wstring paramName,
            SharedType paramType
        );
        
        template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getMinusFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType,
            std::wstring paramName,
            SharedType paramType
        );

        template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getTimesFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType,
            std::wstring paramName,
            SharedType paramType
        );

        template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getDivFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType,
            std::wstring paramName,
            SharedType paramType
        );

        template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getModFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType,
            std::wstring paramName,
            SharedType paramType
        );

        template <typename PrimitiveType, typename ParamValue>
        static inline std::shared_ptr<BuiltInFunScope> getCompareToFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            std::wstring paramName,
            SharedType paramType
        );

        template <typename PrimitiveType>
        static inline std::shared_ptr<BuiltInFunScope> getEqualsFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            std::wstring paramName,
            SharedType paramType
        );

        template <typename PrimitiveType, typename ParamValue>
        static inline std::shared_ptr<BuiltInFunScope> getShrFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType
        );

        template <typename PrimitiveType, typename ParamValue>
        static inline std::shared_ptr<BuiltInFunScope> getShlFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType
        );
        
        template <typename PrimitiveType, typename ParamValue>
        static inline std::shared_ptr<BuiltInFunScope> getBitAndFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType,
            std::wstring paramName
        );
        
        template <typename PrimitiveType, typename ParamValue>
        static inline std::shared_ptr<BuiltInFunScope> getXorFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType,
            std::wstring paramName
        );

        template <typename PrimitiveType, typename ParamValue>
        static inline std::shared_ptr<BuiltInFunScope> getBitOrFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType,
            std::wstring paramName
        );

        template <typename PrimitiveType, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getBitNotFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType
        );
        
        template <typename PrimitiveType, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getToAnotherTypeFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            std::wstring name,
            SharedType returnType
        );

        template <typename PrimitiveType, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getUnaryPlusFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType
        );

        template <typename PrimitiveType, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getUnaryMinusFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType
        );

        template <typename PrimitiveType, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getIncFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType
        );

        template <typename PrimitiveType, typename ReturnValue>
        static inline std::shared_ptr<BuiltInFunScope> getDecFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
            SharedType returnType
        );

        template <typename PrimitiveType>
        static inline std::shared_ptr<BuiltInFunScope> getToIntFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
        );

        template <typename PrimitiveType>
        static inline std::shared_ptr<BuiltInFunScope> getToUIntFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
        );

        template <typename PrimitiveType>
        static inline std::shared_ptr<BuiltInFunScope> getToLongFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
        );

        template <typename PrimitiveType>
        static inline std::shared_ptr<BuiltInFunScope> getToULongFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
        );

        template <typename PrimitiveType>
        static inline std::shared_ptr<BuiltInFunScope> getToFloatFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
        );

        template <typename PrimitiveType>
        static inline std::shared_ptr<BuiltInFunScope> getToDoubleFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
        );

        template <typename PrimitiveType>
        static inline std::shared_ptr<BuiltInFunScope> getToStringFun(
            std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
        );

        static const inline auto INT_PARAM_NAME=L"رقم_صحيح";
        static const inline auto UINT_PARAM_NAME=L"رقم_صحيح_م";
        static const inline auto LONG_PARAM_NAME=L"رقم_كبير";
        static const inline auto ULONG_PARAM_NAME=L"رقم_كبير_م";
        static const inline auto FLOAT_PARAM_NAME=L"رقم_عشري";
        static const inline auto DOUBLE_PARAM_NAME=L"رقم_عشري_م";
        static const inline auto CHAR_PARAM_NAME=L"_حرف";
        static const inline auto STRING_PARAM_NAME=L"_نص";
        static const inline auto BOOL_PARAM_NAME=L"_منطقي";
        static const inline auto UNIT_PARAM_NAME=L"_الوحدة";
        static const inline auto BIT_COUNT_PARAM_NAME=L"عدد_البتات";
        static const inline auto READ_LINE_NAME=L"أدخل_";
        static const inline auto READ_NAME=L"أدخل";
        static const inline auto PRINT_NAME=L"اظهر";
        static const inline auto PRINTLN_NAME=L"اظهر_";
        static const inline auto TO_INT_NAME=L"كصحيح";
        static const inline auto TO_UINT_NAME=L"كصحيح_م";
        static const inline auto TO_LONG_NAME=L"ككبير";
        static const inline auto TO_ULONG_NAME=L"ككبير_م";
        static const inline auto TO_FLOAT_NAME=L"كعشري";
        static const inline auto TO_DOUBLE_NAME=L"كعشري_م";
        static const inline auto TO_BOOL_NAME=L"كمنطقي";
        static const inline auto TO_CHAR_NAME=L"كحرف";
        static const inline auto TO_STRING_NAME=L"كنص";

    public:
        BuiltInFunScope(
            std::wstring name,
            SharedType returnType,
            std::map<std::wstring, SharedType> params,
            std::function<SharedIValue(SharedMap<std::wstring, SharedIValue>)> invokeFun,
            bool isOperator=false
        );

        ~BuiltInFunScope();
        
        SharedIValue invoke(SharedMap<std::wstring, SharedIValue> params);

        static void addBuiltInFunctionsTo(SharedFileScope fileScope);

        static void addBuiltInFunctionsToBuiltInClasses();
};


template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getPlusFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType,
    std::wstring paramName,
    SharedType paramType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::PLUS_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{paramName,paramType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(paramName))->getValue();
            return std::make_shared<ReturnValue>(firstVal+secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getMinusFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType,
    std::wstring paramName,
    SharedType paramType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::MINUS_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{paramName,paramType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(paramName))->getValue();
            return std::make_shared<ReturnValue>(firstVal-secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getTimesFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType,
    std::wstring paramName,
    SharedType paramType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::TIMES_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{paramName,paramType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(paramName))->getValue();
            return std::make_shared<ReturnValue>(firstVal*secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getDivFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType,
    std::wstring paramName,
    SharedType paramType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::DIV_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{paramName,paramType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(paramName))->getValue();
            return std::make_shared<ReturnValue>(firstVal/secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getModFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType,
    std::wstring paramName,
    SharedType paramType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::MOD_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{paramName,paramType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(paramName))->getValue();
            return std::make_shared<ReturnValue>(firstVal%secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getCompareToFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    std::wstring paramName,
    SharedType paramType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::COMPARE_TO_NAME,
        Type::INT,
        std::map<std::wstring, SharedType>{{paramName,paramType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(paramName))->getValue();
            auto compareVal=(firstVal>secondVal)?1:(firstVal<secondVal)?-1:0;
            return std::make_shared<IntValue>(compareVal);
        },
        true
    );
}

template <typename PrimitiveType>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getEqualsFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    std::wstring paramName,
    SharedType paramType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::EQUALS_NAME,
        Type::BOOL,
        std::map<std::wstring, SharedType>{{paramName,paramType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<PrimitiveValue<PrimitiveType>>(params->at(paramName))->getValue();
            auto equalsVal=firstVal==secondVal;
            return std::make_shared<BoolValue>(equalsVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getShrFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::SHR_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{BIT_COUNT_PARAM_NAME,returnType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(BIT_COUNT_PARAM_NAME))->getValue();
            return std::make_shared<ParamValue>(firstVal>>secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getShlFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::SHL_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{BIT_COUNT_PARAM_NAME,returnType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(BIT_COUNT_PARAM_NAME))->getValue();
            return std::make_shared<ParamValue>(firstVal<<secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getBitAndFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType,
    std::wstring paramName
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::BIT_AND_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{paramName,returnType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(paramName))->getValue();
            return std::make_shared<ParamValue>(firstVal&secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getXorFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType,
    std::wstring paramName
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::XOR_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{paramName,returnType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(paramName))->getValue();
            return std::make_shared<ParamValue>(firstVal^secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ParamValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getBitOrFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType,
    std::wstring paramName
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::BIT_OR_NAME,
        returnType,
        std::map<std::wstring, SharedType>{{paramName,returnType}},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto firstVal=classScope->getValue();
            auto secondVal=std::dynamic_pointer_cast<ParamValue>(params->at(paramName))->getValue();
            return std::make_shared<ParamValue>(firstVal|secondVal);
        },
        true
    );
}

template <typename PrimitiveType, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getBitNotFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::BIT_NOT_NAME,
        returnType,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            return std::make_shared<ReturnValue>(~val);
        },
        true
    );
}

template <typename PrimitiveType, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getToAnotherTypeFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    std::wstring name,
    SharedType returnType
){
    return std::make_shared<BuiltInFunScope>(
        name,
        returnType,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            return std::make_shared<ReturnValue>(val);
        },
        true
    );
}

template <typename PrimitiveType, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getUnaryPlusFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::UNARY_PLUS_NAME,
        returnType,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            return std::make_shared<ReturnValue>(val);
        },
        true
    );
}

template <typename PrimitiveType, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getUnaryMinusFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::UNARY_MINUS_NAME,
        returnType,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            return std::make_shared<ReturnValue>(-val);
        },
        true
    );
}

template <typename PrimitiveType, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getIncFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::INC_NAME,
        returnType,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            return std::make_shared<ReturnValue>(++val);
        },
        true
    );
}

template <typename PrimitiveType, typename ReturnValue>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getDecFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope,
    SharedType returnType
){
    return std::make_shared<BuiltInFunScope>(
        OperatorFunctions::DEC_NAME,
        returnType,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            return std::make_shared<ReturnValue>(--val);
        },
        true
    );
}

template <typename PrimitiveType>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getToIntFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
){
    return getToAnotherTypeFun<PrimitiveType, IntValue>(classScope, TO_INT_NAME, Type::INT);
}

template <typename PrimitiveType>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getToUIntFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
){
    return getToAnotherTypeFun<PrimitiveType, UIntValue>(classScope, TO_UINT_NAME, Type::UINT);
}

template <typename PrimitiveType>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getToLongFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
){
    return getToAnotherTypeFun<PrimitiveType, LongValue>(classScope, TO_LONG_NAME, Type::LONG);
}

template <typename PrimitiveType>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getToULongFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
){
    return getToAnotherTypeFun<PrimitiveType, ULongValue>(classScope, TO_ULONG_NAME, Type::ULONG);
}

template <typename PrimitiveType>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getToFloatFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
){
    return getToAnotherTypeFun<PrimitiveType, FloatValue>(classScope, TO_FLOAT_NAME, Type::FLOAT);
}

template <typename PrimitiveType>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getToDoubleFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
){
    return getToAnotherTypeFun<PrimitiveType, DoubleValue>(classScope, TO_DOUBLE_NAME, Type::DOUBLE);
}

template <typename PrimitiveType>
inline std::shared_ptr<BuiltInFunScope> BuiltInFunScope::getToStringFun(
    std::shared_ptr<PrimitiveClassScope<PrimitiveType>> classScope
){
    return std::make_shared<BuiltInFunScope>(
        TO_STRING_NAME,
        Type::STRING,
        std::map<std::wstring, SharedType>{},
        [=](SharedMap<std::wstring, SharedIValue> params){
            auto val=classScope->getValue();
            return std::make_shared<StringValue>(std::to_wstring(val));
        },
        true
    );
}

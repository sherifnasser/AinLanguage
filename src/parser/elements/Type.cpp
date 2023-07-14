#include "Type.hpp"
#include "CharClassScope.hpp"
#include "StringClassScope.hpp"
#include "BoolClassScope.hpp"
#include "UnitClassScope.hpp"
#include "IntClassScope.hpp"
#include "UIntClassScope.hpp"
#include "LongClassScope.hpp"
#include "ULongClassScope.hpp"
#include "FloatClassScope.hpp"
#include "DoubleClassScope.hpp"
#include "FileScope.hpp"
#include <memory>
#include <string>

Type::Type(SharedWString name,SharedClassScope classScope)
:name(name),classScope(classScope){}

bool Type::operator==(const Type& type)const{
    return *this->name==*type.name;
}

bool Type::operator!=(const Type& type)const{
    return !(*this==type);
}

SharedClassScope Type::getClassScope(){
    return classScope;
}

void Type::setClassScope(SharedClassScope classScope){
    this->classScope = classScope;
}

SharedWString Type::getName(){
    return name;
}

SharedWString Type::UNIT_NAME=std::make_shared<std::wstring>(L"الوحدة");
SharedWString Type::INT_NAME=std::make_shared<std::wstring>(L"صحيح");
SharedWString Type::UINT_NAME=std::make_shared<std::wstring>(L"صحيح_م");
SharedWString Type::LONG_NAME=std::make_shared<std::wstring>(L"كبير");
SharedWString Type::ULONG_NAME=std::make_shared<std::wstring>(L"كبير_م");
SharedWString Type::FLOAT_NAME=std::make_shared<std::wstring>(L"عشري");
SharedWString Type::DOUBLE_NAME=std::make_shared<std::wstring>(L"عشري_م");
SharedWString Type::CHAR_NAME=std::make_shared<std::wstring>(L"حرف");
SharedWString Type::STRING_NAME=std::make_shared<std::wstring>(L"نص");
SharedWString Type::BOOL_NAME=std::make_shared<std::wstring>(L"منطقي");

SharedType Type::UNIT=std::make_shared<Type>(
    UNIT_NAME,
    std::make_shared<UnitClassScope>()
);

SharedType Type::CHAR=std::make_shared<Type>(
    CHAR_NAME,
    std::make_shared<CharClassScope>()
);

SharedType Type::INT=std::make_shared<Type>(
    INT_NAME,
    std::make_shared<IntClassScope>()
);

SharedType Type::LONG=std::make_shared<Type>(
    LONG_NAME,
    std::make_shared<LongClassScope>()
);

SharedType Type::FLOAT=std::make_shared<Type>(
    FLOAT_NAME,
    std::make_shared<FloatClassScope>()
);

// صحيح موجب
SharedType Type::UINT=std::make_shared<Type>(
    UINT_NAME,
    std::make_shared<UIntClassScope>()
);

// كبير موجب
SharedType Type::ULONG=std::make_shared<Type>(
    ULONG_NAME,
    std::make_shared<ULongClassScope>()
);

// عشري مزدوج
SharedType Type::DOUBLE=std::make_shared<Type>(
    DOUBLE_NAME,
    std::make_shared<DoubleClassScope>()
);

SharedType Type::BOOL=std::make_shared<Type>(
    BOOL_NAME,
    std::make_shared<BoolClassScope>()
);

SharedType Type::STRING=std::make_shared<Type>(
    STRING_NAME,
    std::make_shared<StringClassScope>()
);


void Type::addBuiltInClassesTo(SharedFileScope fileScope) {
    auto builtInCLasses={
        UNIT,
        INT,UINT,LONG,ULONG,
        FLOAT,DOUBLE,
        CHAR,STRING,
        BOOL
    };
    auto privateClasses=fileScope->getPrivateClasses();
    for(auto builtInClass:builtInCLasses){
        (*privateClasses)[*builtInClass->getName()]=builtInClass->getClassScope();
    }
}
#include "Type.hpp"
#include <memory>
#include <string>

Type::Type(SharedWString name):name(name){}

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

SharedType Type::UNIT=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"الوحدة")
);

SharedType Type::CHAR=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"حرف")
);

SharedType Type::INT=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"صحيح")
);

SharedType Type::LONG=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"كبير")
);

SharedType Type::FLOAT=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"عشري")
);

// صحيح موجب
SharedType Type::UINT=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"صحيح_م")
);

// كبير موجب
SharedType Type::ULONG=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"كبير_م")
);

// عشري مزدوج
SharedType Type::DOUBLE=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"عشري_م")
);

SharedType Type::BOOL=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"منطقي")
);

SharedType Type::STRING=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"نص")
);
#include "Type.hpp"
#include <memory>
#include <string>

Type::Type(SharedWString name):name(name){}

bool Type::operator==(Type& type) {
    return *this->name==*type.name;
}

bool Type::operator!=(Type& type) {
    return !(*this==type);
}

SharedType Type::UNIT=std::make_shared<Type>(
    std::make_shared<std::wstring>(L"الوحدة")
);

#include "TypeParser.hpp"
#include "Type.hpp"
#include "TokensIterator.hpp"
#include <memory>
#include <string>

TypeParser::TypeParser(SharedTokensIterator iterator)
:BaseParser(iterator,nullptr)
{}

SharedType TypeParser::parse(){
    // TODO: parse generics and nullables
    auto typeId=expectIdentifier();
    auto typeName=std::make_shared<std::wstring>(typeId);
    iterator->next();
    auto type=std::make_shared<Type>(typeName);
    return type;
}

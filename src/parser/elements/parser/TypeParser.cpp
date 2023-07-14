#include "TypeParser.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "TokensIterator.hpp"
#include "TypeChecker.hpp"
#include "FileScope.hpp"
#include "BaseScope.hpp"
#include <memory>
#include <string>

TypeParser::TypeParser(
    SharedTokensIterator iterator,
    SharedBaseScope scope,
    SharedITypeChecker typeChecker
):BaseParser(iterator,scope),typeChecker(typeChecker){}

SharedType TypeParser::parse(){
    // TODO: parse generics and nullables
    auto typeId=expectIdentifier();
    auto typeName=std::make_shared<std::wstring>(typeId);    
    auto type=std::make_shared<Type>(typeName);
    auto lineNumber=iterator->lineNumber;
    typeChecker->subscribe(
        lineNumber,scope,type
    );
    iterator->next();
    return type;
}

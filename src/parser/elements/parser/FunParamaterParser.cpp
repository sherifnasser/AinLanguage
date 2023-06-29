#include "FunParamaterParser.hpp"
#include "FunParamater.hpp"
#include "TypeParser.hpp"
#include "SharedPtrTypes.hpp"

FunParamaterParser::FunParamaterParser(SharedTokensIterator iterator)
:BaseParser(iterator,nullptr){}

SharedFunParamater FunParamaterParser::parse(){

    auto nameId=expectIdentifier();

    expectNextSymbol(SymbolToken::COLON);

    iterator->next();

    auto paramName=std::make_shared<std::wstring>(nameId);

    auto paramType=TypeParser(iterator).parse();

    auto param=std::make_shared<FunParamater>(paramName,paramType);

    return param;
}

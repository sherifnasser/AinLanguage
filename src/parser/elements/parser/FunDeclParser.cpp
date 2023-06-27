#include "FunDeclParser.hpp"
#include "FunDecl.hpp"
#include "KeywordToken.hpp"
#include "LexerToken.hpp"
#include "SharedPtrTypes.hpp"
#include "SymbolToken.hpp"
#include "TokensIterator.hpp"
#include "Type.hpp"
#include "TypeParser.hpp"
#include "UnexpectedTokenException.hpp"
#include "FunParamaterParser.hpp"
#include <memory>
#include <string>
#include <vector>

FunDeclParser::FunDeclParser(
    SharedTokensIterator iterator,
    SharedBaseScope scope,
    bool defaultReturnTypeIsUnit
):BaseParser(iterator,scope),defaultReturnTypeIsUnit(defaultReturnTypeIsUnit){}

SharedFunDecl FunDeclParser::parse(){

    if(!iterator->currentMatch(KeywordToken::FUN))
        return nullptr;
    
    auto funNameId=expectNextIdentifier();

    auto funName=std::make_shared<std::wstring>(funNameId);

    expectNextSymbol(SymbolToken::LEFT_PARENTHESIS);

    auto params=std::make_shared<std::vector<SharedFunParamater>>();

    do{

        if(iterator->nextMatch(SymbolToken::RIGHT_PARENTHESIS))
            break;

        auto param=FunParamaterParser(iterator).parse();

        params->push_back(param);
        
    }while(iterator->currentMatch(SymbolToken::COMMA));

    expectSymbol(SymbolToken::RIGHT_PARENTHESIS);

    expectNextSymbol(SymbolToken::COLON);

    iterator->next();
    SharedType funReturnType;
    try{
        funReturnType=TypeParser(iterator).parse();
    }
    catch(UnexpectedTokenException& e){
        if(!defaultReturnTypeIsUnit)
            throw e;
        funReturnType=Type::UNIT;
    }

    auto fun=std::make_shared<FunDecl>(
        funName,
        funReturnType,
        params
    );

    return fun;
}

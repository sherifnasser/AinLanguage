#include "FunDeclParser.hpp"
#include "ConflictingDeclarationException.hpp"
#include "FunDecl.hpp"
#include "KeywordToken.hpp"
#include "LexerToken.hpp"
#include "OperatorFunShouldHaveSingleParamException.hpp"
#include "SharedPtrTypes.hpp"
#include "SymbolToken.hpp"
#include "TokensIterator.hpp"
#include "Type.hpp"
#include "TypeParser.hpp"
#include "UnexpectedTokenException.hpp"
#include "FunParamaterParser.hpp"
#include "FunParamater.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

FunDeclParser::FunDeclParser(
    SharedTokensIterator iterator,
    SharedBaseScope scope
):BaseParser(iterator,scope){}

SharedFunDecl FunDeclParser::parse(){

    if(!iterator->currentMatch(KeywordToken::FUN))
        return nullptr;
    
    auto isOperator=std::make_shared<bool>(false);

    if(iterator->nextMatch(KeywordToken::OPERATOR)){
        *isOperator=true;
        iterator->next();
    }

    auto funNameId=expectIdentifier();

    auto funName=std::make_shared<std::wstring>(funNameId);

    expectNextSymbol(SymbolToken::LEFT_PARENTHESIS);

    auto params=std::make_shared<std::vector<SharedFunParamater>>();

    do{

        if(iterator->nextMatch(SymbolToken::RIGHT_PARENTHESIS))
            break;

        auto param=FunParamaterParser(iterator).parse();

        auto isParamDeclared=std::find_if(
            params->begin(),
            params->end(),
            [&](SharedFunParamater p){return *p->name==*param->name;}
        );

        if(isParamDeclared!=params->end())
            throw ConflictingDeclarationException(iterator->lineNumber);

        params->push_back(param);
        
    }while(iterator->currentMatch(SymbolToken::COMMA));
    
    if(*isOperator&&params->size()!=1)
        throw OperatorFunShouldHaveSingleParamException(iterator->lineNumber);

    expectSymbol(SymbolToken::RIGHT_PARENTHESIS);

    SharedType funReturnType;

    auto colonFound=false;
    
    try{
        expectNextSymbol(SymbolToken::COLON);
        colonFound=true;
    }catch(UnexpectedTokenException& e){}

    if(colonFound){
        iterator->next();
        funReturnType=TypeParser(iterator).parse();
    }

    auto fun=std::make_shared<FunDecl>(
        funName,
        funReturnType,
        isOperator,
        params
    );

    return fun;
}

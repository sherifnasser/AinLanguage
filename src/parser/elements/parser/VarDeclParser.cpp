#include "VarDeclParser.hpp"
#include "KeywordToken.hpp"
#include "SharedPtrTypes.hpp"
#include "TypeParser.hpp"
#include "Type.hpp"
#include <memory>

VarDeclParser::VarDeclParser(
    SharedTokensIterator iterator,
    SharedBaseScope scope,
    bool typeFromExpression
):BaseParser(iterator,scope),typeFromExpression(typeFromExpression){}

SharedVarDecl VarDeclParser::parse(){

    auto isVal=iterator->currentMatch(KeywordToken::VAL);

    if(
        !iterator->currentMatch(KeywordToken::VAR)
        &&
        !isVal
    )
        return nullptr;

    auto nameId=expectNextIdentifier();

    auto name=std::make_shared<std::wstring>(nameId);

    expectNextSymbol(SymbolToken::COLON);

    iterator->next();
    SharedType type;
    
    try{
        type=TypeParser(iterator).parse();
    }
    catch(UnexpectedTokenException& e){
        if(!typeFromExpression)
            throw e;
        type=Type::UNIT;
    }

    auto var=std::make_shared<VarDecl>(
        name,
        type,
        std::make_shared<bool>(isVal)
    );

    return var;
}

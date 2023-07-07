#include "VarStatementParser.hpp"
#include "MustHaveExplicitTypeException.hpp"
#include "ParserProvidersAliases.hpp"
#include "SharedPtrTypes.hpp"
#include "SymbolToken.hpp"
#include "VarDecl.hpp"
#include "VarStm.hpp"
#include "Variable.hpp"
#include <memory>

VarStatementParser::VarStatementParser(
    SharedTokensIterator iterator,
    SharedBaseScope scope,
    VarDeclParserProvider varDeclParserProvider,
    ExpressionParserProvider expressionParserProvider
):
BaseParser(iterator,scope),
varDeclParser(
    varDeclParserProvider(iterator,scope)
),
expressionParser(
    expressionParserProvider(iterator,scope)
)
{}

SharedVarStm VarStatementParser::parse(){
    auto decl=varDeclParser->parse();

    SharedIExpression ex;

    int lineNumber=iterator->lineNumber;

    if(iterator->currentMatch(SymbolToken::EQUAL)){
        iterator->next();
        ex=expressionParser->parse();
    }
    else if(decl->hasImplicitType())
        throw MustHaveExplicitTypeException(lineNumber);
    
    auto var=std::make_shared<Variable>(decl);

    auto stm=std::make_shared<VarStm>(
        lineNumber,
        scope,
        var,
        ex
    );

    return stm;
}

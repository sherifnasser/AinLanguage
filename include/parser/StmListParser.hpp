#pragma once
#include "BaseParser.hpp"
#include "ParserProvidersAliases.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>
class StmListParser:public BaseParser<SharedStmList>{
    private:
        SharedBaseParser<SharedVarStm> varStmParser;
        ExpressionParserProvider expressionParserProvider;
    public:
        StmListParser(
            SharedTokensIterator iterator,
            SharedStmListScope scope,
            VarStmParserProvider varStmParserProvider,
            ExpressionParserProvider expressionParserProvider
        );
        SharedStmList parse()override;
        void parseInScope(SharedStmListScope stmListScope);
        void parseEvenWithNoCurlyBracesInScope(SharedStmListScope stmListScope);
        SharedIStatement parseNextStatement(SharedStmListScope parentScope);
        SharedIStatement parseVarStatement(SharedStmListScope parentScope);
        SharedIStatement parseIfStatement(SharedStmListScope parentScope);
        SharedIStatement parseWhileStatement(SharedStmListScope parentScope);
        SharedIStatement parseDoWhileStatement(SharedStmListScope parentScope);
        SharedIStatement parseReturnStatement(SharedStmListScope parentScope);
        SharedIStatement parseExpressionStatement(SharedStmListScope parentScope);
};
#include "StmListParser.hpp"
#include "ASTVisitor.hpp"
#include "AssignStatement.hpp"
#include "BreakStatement.hpp"
#include "ContinueStatement.hpp"
#include "DoWhileStatement.hpp"
#include "ExpressionExpectedException.hpp"
#include "ExpressionStatement.hpp"
#include "IfStatement.hpp"
#include "KeywordToken.hpp"
#include "LexerToken.hpp"
#include "LoopScope.hpp"
#include "OnlyVariablesAreAssignableException.hpp"
#include "OperatorFunInvokeExpression.hpp"
#include "OperatorFunctions.hpp"
#include "ParserProvidersAliases.hpp"
#include "ReturnStatement.hpp"
#include "SharedPtrTypes.hpp"
#include "StatementExpectedException.hpp"
#include "StmShouldBeUsedInsideLoopException.hpp"
#include "SymbolToken.hpp"
#include "StmListScope.hpp"
#include "Type.hpp"
#include "UnexpectedTokenException.hpp"
#include "UnitExpression.hpp"
#include "VarStm.hpp"
#include "Variable.hpp"
#include "WhileStatement.hpp"
#include <memory>
#include <vector>

StmListParser::StmListParser(
    SharedTokensIterator iterator,
    SharedStmListScope scope,
    VarStmParserProvider varStmParserProvider,
    ExpressionParserProvider expressionParserProvider
)
: BaseParser(iterator,scope),
varStmParser(
    varStmParserProvider(iterator,scope)
),
expressionParserProvider(expressionParserProvider)
{}

SharedStmList StmListParser::parse(){
    
    auto stmListScope=std::dynamic_pointer_cast<StmListScope>(scope);

    parseInScope(stmListScope);

    return stmListScope->getStmList();
}

void StmListParser::parseInScope(SharedStmListScope stmListScope){

    expectSymbol(SymbolToken::LEFT_CURLY_BRACES);
    iterator->next();

    auto stmList=stmListScope->getStmList();
    
    while(iterator->currentTokenType()!=LexerToken::EOF_TOKEN){

        if(iterator->currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
            break;
        
        auto nextStm=parseNextStatement(stmListScope);
        if(nextStm)
            stmListScope->getStmList()->push_back(nextStm);
    }

    expectSymbol(SymbolToken::RIGHT_CURLY_BRACES);

    iterator->next();
}

void StmListParser::parseEvenWithNoCurlyBracesInScope(SharedStmListScope stmListScope){

    if(iterator->currentMatch(SymbolToken::LEFT_CURLY_BRACES)){
        parseInScope(stmListScope);
        return;
    }

    auto nextStm=parseNextStatement(stmListScope);

    if(!nextStm)
        throw StatementExpectedException(iterator->lineNumber);
    
    stmListScope->getStmList()->push_back(nextStm);
}

SharedIStatement StmListParser::parseNextStatement(SharedStmListScope parentScope){

    auto varStm=parseVarStatement(parentScope);
    if(varStm)
        return varStm;

    auto ifStm=parseIfStatement(parentScope);
    if(ifStm)
        return ifStm;

    auto whileStm=parseWhileStatement(parentScope);
    if(whileStm)
        return whileStm;

    auto doWhileStm=parseDoWhileStatement(parentScope);
    if(doWhileStm)
        return doWhileStm;

    auto returnStm=parseReturnStatement(parentScope);
    if(returnStm)
        return returnStm;

    auto breakContinueStm=parseBreakContinueStatement(parentScope);
    if(breakContinueStm)
        return breakContinueStm;

    auto exStm=parseExpressionStatement(parentScope);

    return exStm;

}

SharedIStatement StmListParser::parseVarStatement(SharedStmListScope parentScope) {
    auto varStm=varStmParser->parse();

    if(!varStm)
        return nullptr;
    
    auto var=varStm->getVar();

    (*parentScope->getLocals())[*var->getName()]=var;

    return varStm;
}

SharedIStatement StmListParser::parseIfStatement(SharedStmListScope parentScope){

    if(!iterator->currentMatch(KeywordToken::IF))
        return nullptr;

    int lineNumber=iterator->lineNumber;

    expectNextSymbol(SymbolToken::LEFT_PARENTHESIS);
    
    iterator->next();

    auto conditionEx=expressionParserProvider(iterator,parentScope)->parse();

    if(!conditionEx)
        throw ExpressionExpectedException(iterator->lineNumber);
    
    expectSymbol(SymbolToken::RIGHT_PARENTHESIS);

    auto ifScope=std::make_shared<StmListScope>(L"لو",parentScope);

    iterator->next();

    parseEvenWithNoCurlyBracesInScope(ifScope);

    SharedStmListScope elseScope;

    if(iterator->currentMatch(KeywordToken::ELSE)){
        iterator->next();
        elseScope=std::make_shared<StmListScope>(L"وإلا",parentScope);
        parseEvenWithNoCurlyBracesInScope(elseScope);
    }

    return std::make_shared<IfStatement>(
        lineNumber,
        parentScope,
        conditionEx,
        ifScope,
        elseScope
    );
}

SharedIStatement StmListParser::parseWhileStatement(SharedStmListScope parentScope){
    
    if(!iterator->currentMatch(KeywordToken::WHILE))
        return nullptr;

    int lineNumber=iterator->lineNumber;

    expectNextSymbol(SymbolToken::LEFT_PARENTHESIS);
    
    iterator->next();

    auto conditionEx=expressionParserProvider(iterator,parentScope)->parse();

    if(!conditionEx)
        throw ExpressionExpectedException(iterator->lineNumber);
    
    expectSymbol(SymbolToken::RIGHT_PARENTHESIS);

    auto whileScope=std::make_shared<LoopScope>(parentScope);

    iterator->next();

    parseEvenWithNoCurlyBracesInScope(whileScope);

    return std::make_shared<WhileStatement>(
        lineNumber,
        parentScope,
        conditionEx,
        whileScope
    );
}

SharedIStatement StmListParser::parseDoWhileStatement(SharedStmListScope parentScope){
    
    if(!iterator->currentMatch(KeywordToken::DO))
        return nullptr;

    int lineNumber=iterator->lineNumber;

    auto doWhileScope=std::make_shared<LoopScope>(parentScope);

    iterator->next();

    parseEvenWithNoCurlyBracesInScope(doWhileScope);

    if(!iterator->currentMatch(KeywordToken::WHILE))
        throw UnexpectedTokenException(
            lineNumber,
            LexerToken::stringify(LexerToken::KEYWORD_TOKEN)+L" "+KeywordToken::WHILE.getVal(),
            LexerToken::stringify(iterator->currentTokenType())+L" "+iterator->currentVal()
        );

    expectNextSymbol(SymbolToken::LEFT_PARENTHESIS);
    
    iterator->next();

    auto conditionEx=expressionParserProvider(iterator,parentScope)->parse();

    if(!conditionEx)
        throw ExpressionExpectedException(iterator->lineNumber);
    
    expectSymbol(SymbolToken::RIGHT_PARENTHESIS);

    iterator->next();
    
    return std::make_shared<DoWhileStatement>(
        lineNumber,
        parentScope,
        conditionEx,
        doWhileScope
    );

}

SharedIStatement StmListParser::parseReturnStatement(SharedStmListScope parentScope){
    
    if(!iterator->currentMatch(KeywordToken::RETURN))
        return nullptr;
    
    int lineNumber=iterator->lineNumber;

    iterator->next();

    auto ex=expressionParserProvider(iterator,scope)->parse();

    if(!ex)
        ex=std::make_shared<UnitExpression>(lineNumber);

    return std::make_shared<ReturnStatement>(
        lineNumber,
        parentScope,
        ex
    );
}

SharedIStatement StmListParser::parseBreakContinueStatement(SharedStmListScope parentScope){

    auto isBreak=iterator->currentMatch(KeywordToken::BREAK);
    auto isContinue=iterator->currentMatch(KeywordToken::CONTINUE);

    if(!isBreak&&!isContinue)
        return nullptr;

    auto loopScope=BaseScope::getContainingLoop(parentScope);
    
    int lineNumber=iterator->lineNumber;

    if(!loopScope)
        throw StmShouldBeUsedInsideLoopException(
            lineNumber,
            ((isBreak)?KeywordToken::BREAK.getVal():KeywordToken::CONTINUE.getVal())
        );
    
    iterator->next();

    if(isBreak)
        return std::make_shared<BreakStatement>(lineNumber,parentScope);

    return std::make_shared<ContinueStatement>(lineNumber,parentScope);
}

SharedIStatement StmListParser::parseExpressionStatement(SharedStmListScope parentScope){

    int lineNumber=iterator->lineNumber;

    auto ex=expressionParserProvider(iterator,parentScope)->parse();

    if(!ex)
        return nullptr;
    
    auto op=iterator->currentToken();
    
    if(
        *op!=SymbolToken::EQUAL
        &&
        *op!=SymbolToken::PLUS_EQUAL
        &&
        *op!=SymbolToken::MINUS_EQUAL
        &&
        *op!=SymbolToken::STAR_EQUAL
        &&
        *op!=SymbolToken::SLASH_EQUAL
        &&
        *op!=SymbolToken::MODULO_EQUAL
        &&
        *op!=SymbolToken::POWER_EQUAL
    )
        return std::make_shared<ExpressionStatement>(
            lineNumber,
            parentScope,
            ex
        );
    
    if(!IExpression::isAssignableExpression(ex))
        throw OnlyVariablesAreAssignableException(lineNumber);

    lineNumber=iterator->lineNumber;

    iterator->next();
    
    auto assignExRight=expressionParserProvider(iterator,scope)->parse();

    if(!assignExRight)
        throw ExpressionExpectedException(iterator->lineNumber);

    auto isAugmented=*op!=SymbolToken::EQUAL;
    
    if(isAugmented){

        auto args=std::make_shared<std::vector<SharedIExpression>>(std::vector<SharedIExpression>{assignExRight});

        assignExRight=std::make_shared<OperatorFunInvokeExpression>(
            lineNumber,
            getAssignEqualOpFromToken(*op),
            args,
            ex
        );
    }
        
    return std::make_shared<AssignStatement>(
        lineNumber,
        parentScope,
        ex,
        assignExRight,
        isAugmented
    );
    
}
OperatorFunInvokeExpression::Operator StmListParser::getAssignEqualOpFromToken(LexerToken op){

    if(op==SymbolToken::PLUS_EQUAL)
        return OperatorFunInvokeExpression::Operator::PLUS;
    if(op==SymbolToken::MINUS_EQUAL)
        return OperatorFunInvokeExpression::Operator::MINUS;
    if(op==SymbolToken::STAR_EQUAL)
        return OperatorFunInvokeExpression::Operator::TIMES;
    if(op==SymbolToken::SLASH_EQUAL)
        return OperatorFunInvokeExpression::Operator::DIV;
    if(op==SymbolToken::MODULO_EQUAL)
        return OperatorFunInvokeExpression::Operator::MOD;
    if(op==SymbolToken::POWER_EQUAL)
        return OperatorFunInvokeExpression::Operator::POW;
    
}

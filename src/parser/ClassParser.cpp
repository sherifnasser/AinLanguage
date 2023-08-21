#include "ClassParser.hpp"
#include "BuiltInFunScope.hpp"
#include "ClassScope.hpp"
#include "ConflictingDeclarationException.hpp"
#include "FunDecl.hpp"
#include "FunScope.hpp"
#include "KeywordToken.hpp"
#include "LexerToken.hpp"
#include "ObjectValue.hpp"
#include "SharedPtrTypes.hpp"
#include "SymbolToken.hpp"
#include "Type.hpp"
#include "ainio.hpp"
#include "VarStm.hpp"
#include "Variable.hpp"
#include <memory>
#include <string>

ClassParser::ClassParser(
    SharedTokensIterator iterator,
    SharedBaseScope scope,
    FunParserProvider funParserProvider,
    VarStmParserProvider varStmParserProvider
)
    : BaseParser(iterator,scope),
      funParserProvider(funParserProvider),
      varStmParserProvider(varStmParserProvider){}

SharedClassScope ClassParser::parse(){

    if(!iterator->currentMatch(KeywordToken::CLASS))
        return nullptr;

    auto className=expectNextIdentifier();

    iterator->next();
    // TODO: parse primary constructor and super classes
    expectSymbol(SymbolToken::LEFT_CURLY_BRACES);
    iterator->next();
    

    auto classScope=std::make_shared<ClassScope>(
        className,
        scope
    );
    classScope->setPrimaryConstructor(
        std::make_shared<StmListScope>(
            className,classScope
        )
    );
    

    while(iterator->currentTokenType()!=LexerToken::EOF_TOKEN){

        if(iterator->currentMatch(SymbolToken::RIGHT_CURLY_BRACES))
            break;
        
        auto visibility=parseVisibility();
        
        parseFunScope(visibility,classScope);
        
        parseVarStm(visibility,classScope);

    }
    
    expectSymbol(SymbolToken::RIGHT_CURLY_BRACES);
    iterator->next();

    auto type=std::make_shared<Type>(
        std::make_shared<std::wstring>(className),
        classScope
    );

    if(classScope->getPublicConstructors()->empty()&&classScope->getPrivateConstructors()->empty()){
        // Add default constructor
        (*classScope->getPublicConstructors())[KeywordToken::NEW.getVal()+L"()"]=
        std::make_shared<BuiltInFunScope>(
            KeywordToken::NEW.getVal(),
            type,
            std::map<std::wstring,SharedType>(),
            [=](SharedMap<std::wstring,SharedIValue>){
                auto properties=classScope->runPrimaryConstructor();
                return std::make_shared<ObjectValue>(type,properties);
            }
        );
    }

    return classScope;
}


ClassParser::VisibilityModifier ClassParser::parseVisibility() {
    
    auto visibility=VisibilityModifier::PUBLIC;
    if(iterator->currentMatch(KeywordToken::PUBLIC)){
        iterator->next();
    }
    else if(iterator->currentMatch(KeywordToken::PRIVATE)){
        visibility=VisibilityModifier::PRIVATE;
        iterator->next();
    }

    return visibility;
}

void ClassParser::parseFunScope(VisibilityModifier visibility,SharedClassScope parentScope){

    auto lineNumber=iterator->lineNumber;
    
    auto funScope=funParserProvider(iterator,parentScope)->parse();

    if(!funScope)
        return;
    
    auto decl=funScope->getDecl()->toString();
    if(parentScope->findPrivateFunction(decl)||parentScope->findPublicFunction(decl)){
        throw ConflictingDeclarationException(lineNumber);
    }

    switch (visibility){
        case VisibilityModifier::PUBLIC:
            (*parentScope->getPublicFunctions())[decl]=funScope;
            break;
        case VisibilityModifier::PRIVATE:
            (*parentScope->getPrivateFunctions())[decl]=funScope;
            break;
    }
}

void ClassParser::parseVarStm(VisibilityModifier visibility,SharedClassScope parentScope) {
    
    auto lineNumber=iterator->lineNumber; 
   
    auto varStm=varStmParserProvider(iterator,parentScope)->parse();

    if(!varStm)
        return;
    
    auto var=varStm->getVar();

    auto varName=*var->getName();
    auto primaryConstructor=parentScope->getPrimaryConstructor();
    primaryConstructor->getStmList()->push_back(varStm);

    if(parentScope->findPrivateVariable(varName)||parentScope->findPublicVariable(varName)){
        throw ConflictingDeclarationException(lineNumber);
    }
    
    switch (visibility){
        case VisibilityModifier::PUBLIC:
            (*parentScope->getPublicVariables())[varName]=var;
            break;
        case VisibilityModifier::PRIVATE:
            (*parentScope->getPrivateVariables())[varName]=var;
            break;
    }
}

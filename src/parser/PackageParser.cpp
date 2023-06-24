#include "PackageParser.hpp"
#include "PackageScope.hpp"
#include "BaseParser.hpp"
#include "KeywordToken.hpp"
#include "LexerToken.hpp"
#include "SymbolToken.hpp"
#include "UnexpectedTokenException.hpp"
#include "TokensIterator.hpp"
#include <memory>

SharedPackageScope PackageParser::parse(){
    auto currentPackage=std::dynamic_pointer_cast<PackageScope>(scope);
    
    if(!iterator->currentMatch(KeywordToken::PACKAGE))
        return currentPackage;
    
    currentPackage=addPackageTo(currentPackage);

    while(iterator->currentMatch(SymbolToken::DOT))
        currentPackage=addPackageTo(currentPackage);
    

    return currentPackage;
}

SharedPackageScope PackageParser::addPackageTo(SharedPackageScope parent){

    iterator->next();

    if(iterator->currentTokenType()!=LexerToken::IDENTIFIER_TOKEN)
        throw UnexpectedTokenException(
            iterator->lineNumber,
            LexerToken::stringify(LexerToken::IDENTIFIER_TOKEN),
            LexerToken::stringify(iterator->currentTokenType())
        );

    auto packageName=iterator->currentVal();
    auto foundPackage=parent->findPackageByName(packageName);

    auto newPackage=(foundPackage)
    ?foundPackage
    :std::make_shared<PackageScope>(packageName,parent);

    if(!foundPackage)
        parent->addPackage(newPackage);
    
    iterator->next();

    return newPackage;
}
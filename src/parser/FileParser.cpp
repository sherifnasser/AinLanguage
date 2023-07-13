#include "FileParser.hpp"
#include "KeywordToken.hpp"
#include "LexerToken.hpp"
#include "PackageParser.hpp"
#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "FunScope.hpp"
#include "SharedPtrTypes.hpp"
#include "FunDecl.hpp"
#include <memory>

FileParser::FileParser(
    SharedTokensIterator iterator,
    std::wstring filePath,
    SharedBaseParser<SharedPackageScope> packageParser,
    FunParserProvider funParserProvider
)
:BaseParser(iterator,nullptr),
filePath(filePath),
packageParser(packageParser),
funParserProvider(funParserProvider)
{}


SharedFileScope FileParser::parse(){
    auto package=packageParser->parse();
    scope=package;
    auto file=std::make_shared<FileScope>(filePath,package);
    package->addFile(file);

    while(iterator->currentTokenType()!=LexerToken::EOF_TOKEN){

        auto isPublic=true;

        if(iterator->currentMatch(KeywordToken::PUBLIC)){
            iterator->next();
        }
        else if(iterator->currentMatch(KeywordToken::PRIVATE)){
            isPublic=false;
            iterator->next();
        }
        
        auto funScope=funParserProvider(iterator,file)->parse();
        
        if(funScope){
            auto package=BaseScope::toPackageScope(scope);
            auto decl=funScope->getDecl()->toString();
            if(isPublic){
                // TODO: check is added before
                (*file->getPublicFunctions())[decl]=funScope;
            }
            else{
                (*file->getPrivateFunctions())[decl]=funScope;
            }
        }

    }

    return file;
}

std::wstring FileParser::getFilePath(){
    return filePath;
}
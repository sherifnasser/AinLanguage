#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include "BuiltInFunScope.hpp"
#include "ClassParser.hpp"
#include "ExpressionParser.hpp"
#include "FileParser.hpp"
#include "FunDeclParser.hpp"
#include "FunParamParser.hpp"
#include "FunParser.hpp"
#include "PackageParser.hpp"
#include "PackageScope.hpp"
#include "ParserProvidersAliases.hpp"
#include "SemanticsChecksVisitor.hpp"
#include "SharedPtrTypes.hpp"
#include "AinFile.hpp"
#include "Lexer.hpp"
#include "KeywordToken.hpp"
#include "StmListParser.hpp"
#include "SymbolToken.hpp"
#include "TokensIterator.hpp"
#include "TypeChecker.hpp"
#include "ImplicitVarTypeChecker.hpp"
#include "TypeParser.hpp"
#include "VarDeclParser.hpp"
#include "VarStatementParser.hpp"
#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "FunScope.hpp"
#include "Type.hpp"

auto typeParserProvider=[](SharedTokensIterator iterator,SharedBaseScope scope){
    return std::make_shared<TypeParser>(
        iterator,scope,Semantics::TypeChecker::getInstance()
    );
};

auto funParamParserProvider=[](
    SharedTokensIterator iterator,SharedBaseScope scope,TypeParserProvider typeParserProvider
){
    return std::make_shared<FunParamParser>(
        iterator,scope,typeParserProvider
    );
};

auto varDeclParserProvider=[](SharedTokensIterator iterator,SharedBaseScope scope){
    return std::make_shared<VarDeclParser>(
        iterator,scope,typeParserProvider
    );
};

auto expressionParserProvider=[](SharedTokensIterator iterator,SharedBaseScope scope){
    return std::make_shared<ExpressionParser>(
        iterator,scope,typeParserProvider
    );
};

auto varStmParserProvider=[](SharedTokensIterator iterator,SharedBaseScope scope){
    return std::make_shared<VarStatementParser>(
        iterator,scope,varDeclParserProvider,expressionParserProvider
    );
};

auto stmListParserProvider=[](SharedTokensIterator iterator,SharedStmListScope scope){
    return std::make_shared<StmListParser>(
        iterator,scope,varStmParserProvider,expressionParserProvider
    );
};

auto funDeclParserProvider=[](SharedTokensIterator iterator,SharedBaseScope scope){
    return std::make_shared<FunDeclParser>(
        iterator,scope,typeParserProvider,funParamParserProvider
    );
};

auto funParserProvider=[](SharedTokensIterator iterator,SharedBaseScope scope){
    return std::make_shared<FunParser>(
        iterator,scope,funDeclParserProvider,stmListParserProvider
    );
};

auto classParserProvider=[](SharedTokensIterator iterator,SharedBaseScope scope){
    return std::make_shared<ClassParser>(
        iterator,
        scope,
        stmListParserProvider,
        typeParserProvider,
        funParamParserProvider,
        funParserProvider,
        varStmParserProvider
    );
};

void readAndParse(std::string path){
    auto file=std::make_shared<AinFile>(path);
    auto lexer=std::make_shared<Lexer>(file);
    auto tokens=lexer->getTokens();
    auto iterator=std::make_shared<TokensIterator>(*tokens);
    auto packageParser=std::make_shared<PackageParser>(iterator,PackageScope::AIN_PACKAGE);
    auto wpath=toWstring(path);
    auto fileScope=
        FileParser(
            iterator,
            wpath,
            packageParser,
            funParserProvider,
            classParserProvider,
            varStmParserProvider
        ).parse();

    Type::addBuiltInClassesTo(fileScope);
    BuiltInFunScope::addBuiltInFunctionsTo(fileScope);

}

bool isMainFileOption(std::string o){
    return o=="-m" || o=="--main";
}

int main(int argc, char * argv[]){

    // TODO: show info about ain and available options
    if(argc < 2){ // 2 as it includes the program name
        std::__throw_out_of_range("You should pass at least one ain file path.");
        return -1;
    }

    try{

        // default is first file
        std::string mainPath(argv[1]);

        // to make sure that -m or --main is used only once 
        auto mainOptionUsed=false;

        // parse in reverse and make the main file at the end
        for(int i=argc-1;i>=1;i--){
            if(isMainFileOption(argv[i-1])){
                if(mainOptionUsed)
                    throw std::invalid_argument("\033[1;31mأمر -m أو --main يجب أن يُستخدم مرة واحدة فقط.\033[0m");
                mainPath=std::string(argv[i]);
                mainOptionUsed=true;
                i--;
                continue;
            }
            readAndParse(argv[i]);
        }
        readAndParse(mainPath);

        BuiltInFunScope::addBuiltInFunctionsToBuiltInClasses();

        Semantics::TypeChecker::getInstance()->check();
        

        auto checker=new SemanticsChecksVisitor;

        Semantics::ImplicitVarTypeChecker::getInstance()->check(checker);

        PackageScope::AIN_PACKAGE->accept(checker);
        
        delete checker;

        PackageScope::AIN_PACKAGE->initGlobalVars();

        auto main=PackageScope::AIN_PACKAGE->
            findFileByPath(toWstring(mainPath))->
            findPublicFunction(L"البداية()");

        main->invoke(std::make_shared<std::map<std::wstring, SharedIValue>>());

    }
    catch(std::exception& e){
        std::cout<<e.what()<<std::endl;
    }
    

    return 0;
}
#include "BaseScope.hpp"
#include "FileScope.hpp"
#include "IExpression.hpp"
#include "LexerLine.hpp"
#include "LiteralExpression.hpp"
#include "PackageScope.hpp"
#include "SharedPtrTypes.hpp"
#include "TokensIterator.hpp"
#include "ExpressionParser.hpp"
#include "Type.hpp"
#include "ainio.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace{
    struct FakeTypeParser:public BaseParser<SharedType>{
        int calledTimes=0;
        FakeTypeParser(SharedTokensIterator iterator)
        :BaseParser(iterator,nullptr){}
        
        SharedType parse()override{
            auto type=std::make_shared<Type>(
                std::make_shared<std::wstring>(iterator->currentVal())
            );
            iterator->next();
            calledTimes++;
            return type;
        }

    };
}

int main(){

    auto scope = std::make_shared<FileScope>(L"Pretty print",PackageScope::AIN_PACKAGE);
    
    ainprint(L"Enter expression: ", true);
    std::wstring line=ainread(true);
    LexerLine lexerLine(line,1);

    lexerLine.tokenize();

    auto tokens=lexerLine.getTokens();

    auto iterator=std::make_shared<TokensIterator>(*tokens);

    auto fakeTypeParser=std::make_shared<FakeTypeParser>(iterator);

    auto fakeTypeParserProvider=[&](SharedTokensIterator,SharedBaseScope){
        return fakeTypeParser;
    };

    ExpressionParser parser(iterator,scope,fakeTypeParserProvider);

    //ainprint(std::to_wstring(fakeTypeParser->calledTimes)+L" times",true);

    auto prints=parser.parse()->prettyPrint();

    for(auto& print:prints){
        ainprint(print, true);
    }

    return 0;
}
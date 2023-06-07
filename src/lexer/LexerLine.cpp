#include<iostream>
#include<memory>
#include<vector>
#include<limits>
#include<algorithm>
#include"LexerLine.hpp"
#include"LiteralToken.hpp"
#include"NumberToken.hpp"
#include"SymbolToken.hpp"
#include"KeywordToken.hpp"
#include"wchar_t_helper.hpp"
#include"string_helper.hpp"
#include"StringIsNotClosedException.hpp"
#include"UnsupportedTokenException.hpp"
#include"IllegalUnderscoreException.hpp"
#include"OutOfRangeException.hpp"
#include"InvalidNumberSystemDigitException.hpp"
#include"InvalidIdentifierNameException.hpp"

LexerLine::LexerLine(std::wstring &line,int lineNumber):line(line),lineNumber(lineNumber){
    this->tokens=std::make_shared<std::vector<std::shared_ptr<LexerToken>>>();
}

std::shared_ptr<std::vector<std::shared_ptr<LexerToken>>> LexerLine::getTokens(){
    return this->tokens;
}

int LexerLine::getLineNumber(){
    return this->lineNumber;
}

bool LexerLine::isNotNullToken(std::shared_ptr<LexerToken> token){
    if(token==nullptr)
        return false;
    tokens->push_back(token);
    return true;
}

void LexerLine::tokenize(){
    int i=0;
    while(i<line.size()){
        
        auto stringToken=findStringLiteralToken(&i);
        if(isNotNullToken(stringToken))
            continue;
        
        auto commentToken=findCommentToken(&i);
        if(isNotNullToken(commentToken))
            continue;
        
        auto symbolToken=findSymbolToken(&i);
        if(isNotNullToken(symbolToken))
            continue;

        auto numberToken=findNumberToken(&i);
        if(isNotNullToken(numberToken))
            continue;

        auto identifierOrKeywordToken=findIdentifierOrKeywordToken(&i);
        if(isNotNullToken(identifierOrKeywordToken))
            continue;
        
        // next char is space, so skip it
        i++;
    }
}

std::shared_ptr<LexerToken> LexerLine::findStringLiteralToken(int* startIndex){
    
    auto &c=line[*startIndex];
    auto DOUBLE_QOUTE=L'\"';
    std::wstring CNTRL_DOUBLE_QOUTE=L"\\\""; // when there is double qoute inside the string

    if(c!=DOUBLE_QOUTE)
        return nullptr;

    std::wstring word=L"\"";  // add current "
    int i=++(*startIndex);
    // append every char in the line until finding another "

    while(i<line.size()){

        auto nextCnrtlDoubleQouteIndex=line.find(CNTRL_DOUBLE_QOUTE,i);

        if(nextCnrtlDoubleQouteIndex != std::wstring::npos){
            i=nextCnrtlDoubleQouteIndex+2; // get the char after \" (after 2 chars)
            continue;
        }

        // no more cntrl \" in the string

        auto lastDoubleQouteIndex=line.find(DOUBLE_QOUTE,i);  

        if(lastDoubleQouteIndex == std::wstring::npos){ // string isn't closed
            break;
        }
        auto nextStartIndex=lastDoubleQouteIndex+1;

        word+=line.substr(*startIndex,nextStartIndex-*startIndex);
        auto token=std::make_shared<LiteralToken>(LiteralToken::STRING,word);
        *startIndex=nextStartIndex;
        return token;
    }

    word+=line.substr(*startIndex);
    throw StringIsNotClosedException(lineNumber,word);
}

std::shared_ptr<LexerToken> LexerLine::findCommentToken(int* startIndex){

    auto commentIndex=line.find(L"//",*startIndex);

    if(commentIndex!=*startIndex)
        return nullptr;
    
    auto comment=line.substr(commentIndex);
    auto token=std::make_shared<LexerToken>(LexerToken::COMMENT_TOKEN,comment);
    *startIndex=line.size();  // end of the line, so it'll stop the loop
    return token;
}


std::shared_ptr<LexerToken> LexerLine::findSymbolToken(int* startIndex){
    
    // find a double-symbol token (>=, <=, ==, !=, &&, ||) also assignment operators
    SymbolToken doubleSymbolTokens[]={
        SymbolToken::GREATER_EQUAL,
        SymbolToken::LESS_EQUAL,
        SymbolToken::EQUAL_EQUAL,
        SymbolToken::NOT_EQUAL,
        SymbolToken::LOGICAL_AND,
        SymbolToken::LOGICAL_OR,
        SymbolToken::PLUS_EQUAL,
        SymbolToken::MINUS_EQUAL,
        SymbolToken::STAR_EQUAL,
        SymbolToken::SLASH_EQUAL,
        SymbolToken::MODULO_EQUAL,
        SymbolToken::POWER_EQUAL
    };
    for(auto &s:doubleSymbolTokens){
        auto found=line.find(s.getVal(),*startIndex);
        if(found!=*startIndex)
            continue;
        *startIndex+=2; // skip next symbol
        auto token=std::make_shared<SymbolToken>(s);
        return token;
    }

    // find a single-symbol token
    auto &c=line[*startIndex];
    if(!isainpunct(c)) // This excludes underscore
        return nullptr;
    
    ++(*startIndex);
    std::wstring val;
    val=c;
    auto token=std::make_shared<SymbolToken>(val);
    return token;
}

std::shared_ptr<LexerToken> LexerLine::findNumberToken(int* startIndex){

    if(!iswdigit(line[*startIndex]))
        return nullptr;
    
    int nextStartIndex=*startIndex;

    NUM_SYS numSys=NUM_SYS::DEC;
    auto numType=NumberToken::INT;

    /**
     * Skip after a digit array in a non-decimal number system.
     * If skipped, then change [numSys] and don't skip any more.
    */
    for(auto nS:{NUM_SYS::BIN, NUM_SYS::OCT, NUM_SYS::HEX}){
        skipAfterNonDecIntDigitArray(&nextStartIndex,nS);
        if(nextStartIndex!=*startIndex){
            numSys=nS;
            break;
        }
    }

    /**
     * If numSys didn't change from previos loop,
     * then skip after a digit array in decimal and change the number type (int, double or float)
    */
    if(numSys==NUM_SYS::DEC)
        numType=skipAfterDecDigitArray(&nextStartIndex);
    
    auto number=line.substr(*startIndex,nextStartIndex-*startIndex);

    // remove underscores
    removeUnderscores(&number);

    *startIndex=nextStartIndex;

    switch(numType){
        case NumberToken::DOUBLE:
            getDoubleNumberToken(&number);
            break;
        case NumberToken::FLOAT:
            getFloatNumberToken(&number);
            break;
        default: // INT
            getIntNumberToken(startIndex,&number,&numType,numSys);
    }

    auto token=std::make_shared<NumberToken>(numType,number);
    return token;
}

void LexerLine::skipAfterNonDecIntDigitArray(int* startIndex,NUM_SYS numSys){
    
    if(line[*startIndex]!=L'0')
        return;
    
    // If error occured, we can show the start of number to error index with this
    auto absoluteStartIndex=*startIndex;

    auto nextStartIndex=*startIndex+1;
    auto &numSysCharLine=line[nextStartIndex];

    wchar_t numSysChar;
    switch(numSys)
    {
        case BIN:
            numSysChar=L'b';
            break;
        case OCT:
            numSysChar=L'o';
            break;
        case HEX:
            numSysChar=L'x';
            break;
        default:
            std::__throw_runtime_error("function `skipAfterNonDecNumSystemInt` is only for non-decimal numbers");
    }

    if(std::towlower(numSysCharLine)!=numSysChar)
        return;
    
    nextStartIndex++;

    skipAfterDigitArray(&nextStartIndex,&absoluteStartIndex,numSys);

    auto &stopChar=line[nextStartIndex]; // where the skipping stopped

    // user types 0b12, ob1a, 0O128, ,0b12s, 0xfg etc.
    if (
        (iswxdigit(stopChar) && numSys!=NUM_SYS::HEX)
        ||
        isainalpha(stopChar)
    )
        throw InvalidNumberSystemDigitException(
            lineNumber,
            line.substr(absoluteStartIndex,nextStartIndex-absoluteStartIndex+1)
        );

    *startIndex=nextStartIndex;
}

NumberToken::NUMBER_TYPE LexerLine::skipAfterDecDigitArray(int* startIndex){


    // If error occured, we can show the start of number to error index with this
    auto absoluteStartIndex=*startIndex;

    auto nextStartIndex=*startIndex;

    auto getErrorNumberToken=[&](){
        return line.substr(absoluteStartIndex,nextStartIndex-absoluteStartIndex+1);
    };

    auto numType=NumberToken::INT;

    skipAfterDigitArray(&nextStartIndex,&absoluteStartIndex);

    // number before dot may be treated as object, so check if after the dot is a digit to build the double
    if(line[nextStartIndex]==L'.' && iswdigit(line[nextStartIndex+1])){
        numType=NumberToken::DOUBLE;
        ++nextStartIndex;
        skipAfterDigitArray(&nextStartIndex,&absoluteStartIndex);
    }

    if(std::towlower(line[nextStartIndex])==L'e'){
        numType=NumberToken::DOUBLE; // may be doesn't have a dot, so reassign it to DOUBLE

        ++nextStartIndex;

        if(line[nextStartIndex]==L'-'||line[nextStartIndex]==L'+') // sign of exponent
            nextStartIndex++;

        if(line[nextStartIndex]==L'_')
            throw IllegalUnderscoreException(lineNumber,getErrorNumberToken());

        if(!iswdigit(line[nextStartIndex]))
            throw UnsupportedTokenException(lineNumber,getErrorNumberToken());

        auto before=nextStartIndex;

        // skip after checking next char
        skipAfterDigitArray(&nextStartIndex,&absoluteStartIndex);

        // if nextStartIndex didn't change from skip, error will be thrown
        if(nextStartIndex==before)
            throw UnsupportedTokenException(lineNumber,getErrorNumberToken());
    }

    if(std::towlower(line[nextStartIndex])==L'f'){
        numType=NumberToken::FLOAT;
        nextStartIndex++;
    }

    *startIndex=nextStartIndex;

    wchar_t stopChar=std::towlower(line[nextStartIndex]);

    if(!isainalpha(stopChar))
        return numType;

    /**
     * The number token has an alphabet (which isn't valid for decimal system numbers)
    */

   // numType is float or double
    if(numType!=NumberToken::INT)
        throw UnsupportedTokenException(lineNumber,getErrorNumberToken());

    // numType is int
    if(stopChar!=L'u'&&stopChar!=L'l') // checking for stopChar after unsinged and long types is in getIntNumberToken
        throw InvalidIdentifierNameException(lineNumber,getErrorNumberToken());
    
    // Nothing happened, numType will be unsigned int, unsigned long or long in getIntNumberToken
    return numType;
}

void LexerLine::skipAfterDigitArray(int* startIndex, int* absoluteStartIndex,NUM_SYS numSys){
    auto isNumSysDigit=[&](wchar_t &c){
        switch(numSys)
        {
            case BIN:
                return iswbdigit(c);
            case OCT:
                return iswodigit(c);
            case HEX:
                return (bool)std::iswxdigit(c);
            default:
                return (bool)std::iswdigit(c);
        }
    };

    // number may be 0b, 0o, ox, so throw an error
    if(!isNumSysDigit(line[*startIndex]))
        throw InvalidNumberSystemDigitException(
            lineNumber,
            line.substr(*absoluteStartIndex,*startIndex-*absoluteStartIndex+1)
        );

    int i=*startIndex;
    while(i<line.size() && (isNumSysDigit(line[i])||line[i]==L'_'))
        i++;

    if(line[i-1]==L'_') // must be no underscore at the end
        throw IllegalUnderscoreException(lineNumber,line.substr(*absoluteStartIndex,i-*absoluteStartIndex+1));

    *startIndex=i;
}

void LexerLine::getIntNumberToken(
    int *startIndex,
    std::wstring* number,
    NumberToken::NUMBER_TYPE* numType,
    NUM_SYS numSys
){

    int nextStartIndex=*startIndex;

    if(numSys!=DEC)
        *number=number->substr(2); // skip prefix to not struggle with stoull
    
    // TODO: May prevent leading zeros in integers
    unsigned long long num;
    try{
        num=std::stoull(*number,0,numSys);
    }catch(std::out_of_range e){
        throw OutOfRangeException(lineNumber,*number);
    }

    // May be int or long or unsigned of them

    /**
     * The unary minus from parser may change the numType if the num reached the limits of int or long
    */

    auto isUnsigned=line[nextStartIndex]==L'U'||line[nextStartIndex]==L'u';
    if(isUnsigned){
        *numType=
        (num<=std::numeric_limits<unsigned int>::max())
        ?NumberToken::UNSIGNED_INT
        :NumberToken::UNSIGNED_LONG;
        nextStartIndex++;
    }
    else{
        *numType=
        (num<=std::numeric_limits<int>::max())
        ?NumberToken::INT
        :(num<=std::numeric_limits<long long>::max())
        ?NumberToken::LONG
        :throw OutOfRangeException(lineNumber,*number);
    }

    auto isLong=line[nextStartIndex]==L'L'||line[nextStartIndex]==L'l';
    if(isLong){
        *numType=
        (isUnsigned)
        ?NumberToken::UNSIGNED_LONG
        :NumberToken::LONG;
        nextStartIndex++;
    }

    wchar_t stopChar=line[nextStartIndex];
    
    if(isainalpha(stopChar))
        throw InvalidIdentifierNameException(
            lineNumber,
            *number+line.substr(*startIndex,nextStartIndex-*startIndex+1)
        );
    *startIndex=nextStartIndex;
    *number=std::to_wstring(num);
}

void LexerLine::getDoubleNumberToken(std::wstring* number){
    try{
        auto doubleNum=std::stold(*number);
        *number=std::to_wstring(doubleNum);
    }
    catch(std::out_of_range e){
        throw OutOfRangeException(lineNumber,*number);
    }
}

void LexerLine::getFloatNumberToken(std::wstring* number){
    try{
        auto floatNum=std::stof(*number);
        *number=std::to_wstring(floatNum);
    }
    catch(std::out_of_range e){
        throw OutOfRangeException(lineNumber,*number);
    }
}

std::shared_ptr<LexerToken> LexerLine::findIdentifierOrKeywordToken(int* startIndex){
    int i=*startIndex;

    // Identifiers nad tokens don't start with digits, symbols or spaces
    if(!isainalpha(line[i]))
        return nullptr;
    
    do i++;
    while(isainalpha(line[i])||iswdigit(line[i])); // if next char is alpha or digit add it

    auto val=line.substr(*startIndex,i-*startIndex);

    auto tokenType=(KeywordToken::iskeyword(val))
    ?LexerToken::KEYWORD_TOKEN:LexerToken::IDENTIFIER_TOKEN;

    *startIndex=i; // The new index at which the next token starts

    auto token=std::make_shared<LexerToken>(tokenType,val);
    return token;
}
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
#include"MissingQouteException.hpp"
#include"UnsupportedTokenException.hpp"
#include"IllegalUnderscoreException.hpp"
#include"OutOfRangeException.hpp"
#include"InvalidNumberSystemDigitException.hpp"
#include"InvalidIdentifierNameException.hpp"

LexerLine::LexerLine(std::wstring &line,int lineNumber){
    this->line=line;
    this->lineNumber=lineNumber;
    this->tokens=std::make_shared<std::vector<SharedLexerToken>>();
}

bool LexerLine::isNotNullToken(SharedLexerToken token){
    if(token==nullptr)
        return false;
    tokens->push_back(token);

    // move to the next token, start and end will be equal
    tokenStartIndex=++tokenEndIndex;
    return true;
}

std::wstring LexerLine::getCurrentTokenVal(){
    return line.substr(tokenStartIndex,tokenEndIndex-tokenStartIndex+1);
}

wchar_t LexerLine::charAt(int index){
    if(index<line.size())
        return line[index];
    
    return L'\0';
}

void LexerLine::tokenize(){

    while(tokenStartIndex<line.size()){
        
        auto stringToken=findStringToken();
        if(isNotNullToken(stringToken))
            continue;
        
        auto commentToken=findCommentToken();
        if(isNotNullToken(commentToken))
            continue;
        
        auto symbolToken=findSymbolToken();
        if(isNotNullToken(symbolToken))
            continue;

        auto numberToken=findNumberToken();
        if(isNotNullToken(numberToken))
            continue;

        auto identifierOrKeywordToken=findIdentifierOrKeywordToken();
        if(isNotNullToken(identifierOrKeywordToken))
            continue;
        
        // To skip spaces and tabs, move to the next token, start and end will be equal
        tokenStartIndex=++tokenEndIndex;
    }
}

SharedLexerToken LexerLine::findStringToken(){
    
    auto c=charAt(tokenStartIndex);
    auto DOUBLE_QOUTE=L'\"';
    std::wstring CNTRL_DOUBLE_QOUTE=L"\\\""; // when there is double qoute inside the string

    if(c!=DOUBLE_QOUTE)
        return nullptr;

    ++tokenEndIndex; // the end must be after first double qoute
    
    // append every char in the line until finding another "
    while(tokenEndIndex<line.size()){

        auto nextCnrtlDoubleQouteIndex=line.find(CNTRL_DOUBLE_QOUTE,tokenEndIndex);

        if(nextCnrtlDoubleQouteIndex != std::wstring::npos){
            tokenEndIndex=nextCnrtlDoubleQouteIndex+2; // get the char after \" (after 2 chars)
            continue;
        }

        // no more cntrl \" in the string

        auto lastDoubleQouteIndex=line.find(DOUBLE_QOUTE,tokenEndIndex);  

        if(lastDoubleQouteIndex == std::wstring::npos){ // string isn't closed
            break;
        }

        tokenEndIndex=lastDoubleQouteIndex;

        auto token=std::make_shared<LiteralToken>(LiteralToken::STRING,getCurrentTokenVal());
        return token;
    }

    throw MissingQouteException(lineNumber,getCurrentTokenVal());
}

SharedLexerToken LexerLine::findCharToken(){

    auto c=charAt(tokenStartIndex);
    auto SINGLE_QOUTE=L'\'';
    if(c!=SINGLE_QOUTE)
        return nullptr;
    
}

SharedLexerToken LexerLine::findCommentToken(){

    auto commentIndex=line.find(L"//",tokenStartIndex);

    // may be there is a comment in the line but there're tokens before it, so return to tokenize them
    if(commentIndex!=tokenStartIndex)
        return nullptr;
    
    auto comment=line.substr(commentIndex);
    auto token=std::make_shared<LexerToken>(LexerToken::COMMENT_TOKEN,comment);
    tokenEndIndex=line.size()-1;  // last character in comment
    return token;
}


SharedLexerToken LexerLine::findSymbolToken(){
    
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
        auto found=line.find(s.getVal(),tokenStartIndex);
        if(found!=tokenStartIndex)
            continue;
        tokenEndIndex++; // skip next symbol
        auto token=std::make_shared<SymbolToken>(s);
        return token;
    }

    // find a single-symbol token
    auto c=charAt(tokenStartIndex);
    if(!isainpunct(c)) // This excludes underscore
        return nullptr;
    
    auto token=std::make_shared<SymbolToken>(getCurrentTokenVal());
    return token;
}

SharedLexerToken LexerLine::findNumberToken(){

    if(!iswdigit(charAt(tokenStartIndex)))
        return nullptr;

    NUM_SYS numSys=NUM_SYS::DEC;
    auto numType=NumberToken::INT;

    /**
     * Skip after a digit array in a non-decimal number system.
     * If skipped, then change [numSys] and don't skip any more.
    */
    for(auto nS:{NUM_SYS::BIN, NUM_SYS::OCT, NUM_SYS::HEX}){
        skipAfterNonDecIntDigitArray(nS);
        if(tokenEndIndex!=tokenStartIndex){
            numSys=nS;
            break;
        }
    }

    /**
     * If numSys didn't change from previos loop,
     * then skip after a digit array in decimal and change the number type (int, double or float)
    */
    if(numSys==NUM_SYS::DEC)
        numType=skipAfterDecDigitArray();
    
    auto number=getCurrentTokenVal();

    // remove underscores
    removeUnderscores(&number);

    switch(numType){
        case NumberToken::DOUBLE:
            getDoubleNumberToken(&number);
            break;
        case NumberToken::FLOAT:
            getFloatNumberToken(&number);
            break;
        default: // INT
            getIntNumberToken(&number,&numType,numSys);
    }

    auto token=std::make_shared<NumberToken>(numType,number);
    return token;
}

void LexerLine::skipAfterNonDecIntDigitArray(NUM_SYS numSys){
    
    if(charAt(tokenStartIndex)!=L'0')
        return;
    
    auto numSysCharLine=charAt(tokenStartIndex+1);

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

    // to skip the zero and numSysChar
    tokenEndIndex++;
    skipAfterDigitArray(tokenEndIndex+1,numSys);

    auto stopChar=charAt(tokenEndIndex+1); // where the skipping stopped

    // user types 0b12, ob1a, 0O128, ,0b12s, 0xfg etc.
    if (
        (iswxdigit(stopChar) && numSys!=NUM_SYS::HEX)
        ||
        isainalpha(stopChar)
    )
        throw InvalidNumberSystemDigitException(lineNumber,getCurrentTokenVal()+stopChar);
}

NumberToken::NUMBER_TYPE LexerLine::skipAfterDecDigitArray(){

    auto numType=NumberToken::INT;

    skipAfterDigitArray(tokenStartIndex);

    // number before dot may be treated as object, so check if after the dot is a digit to build the double
    if(charAt(tokenEndIndex+1)==L'.' && iswdigit(charAt(tokenEndIndex+2))){
        numType=NumberToken::DOUBLE;
        tokenEndIndex++; // add '.' symbol to the token
        skipAfterDigitArray(tokenEndIndex+1);
    }

    if(std::towlower(charAt(tokenEndIndex+1))==L'e'){
        numType=NumberToken::DOUBLE; // may be doesn't have a dot, so reassign it to DOUBLE

        // add 'e' symbol to the token
        tokenEndIndex++;

        if(charAt(tokenEndIndex+1)==L'-'||charAt(tokenEndIndex+1)==L'+') // sign of exponent
            tokenEndIndex++; // add the sign to token

        // when character after exponent is underscore
        auto nextChar=charAt(tokenEndIndex+1);
        if(nextChar==L'_')
            throw IllegalUnderscoreException(lineNumber,getCurrentTokenVal()+nextChar); // append nextChar

        // when character after exponent isn't a digit
        if(!iswdigit(nextChar))
            throw UnsupportedTokenException(lineNumber,getCurrentTokenVal()+nextChar); // append nextChar

        auto skipStart=tokenEndIndex+1;

        // skip after checking next char
        skipAfterDigitArray(skipStart);

        // if tokenEndIndex didn't change after skip, error will be thrown
        // this when number ends with exponent without numbers after 'e' symbol (e.g., 10e, 2e+, 3e-)
        if(tokenEndIndex==skipStart-1)
            throw UnsupportedTokenException(lineNumber,getCurrentTokenVal());
    }

    if(std::towlower(charAt(tokenEndIndex+1))==L'f'){
        numType=NumberToken::FLOAT;
        tokenEndIndex++; // add 'f' symbol to the token
    }

    wchar_t stopChar=std::towlower(charAt(tokenEndIndex+1));

    if(!isainalpha(stopChar))
        return numType;

    /**
     * The number token has an alphabet (which isn't valid for decimal system numbers)
    */

   // numType is float or double
    if(numType!=NumberToken::INT)
        throw UnsupportedTokenException(lineNumber,getCurrentTokenVal()+stopChar); // append stopChar
    

    // numType is int
    // checking for stopChar after unsinged and long types is in getIntNumberToken
    if(stopChar!=L'u'&&stopChar!=L'l')
        throw InvalidIdentifierNameException(lineNumber,getCurrentTokenVal()+stopChar); // append stopChar
    
    
    // Nothing happened, numType will be unsigned int, unsigned long or long in getIntNumberToken
    return numType;
}

void LexerLine::skipAfterDigitArray(int startFrom,NUM_SYS numSys){
    auto isNumSysDigit=[&](wchar_t &&c){
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
    if(!isNumSysDigit(charAt(startFrom)))
        throw InvalidNumberSystemDigitException(lineNumber,getCurrentTokenVal()+charAt(startFrom)); // apend next char

    int i=startFrom+1;
    while(i<line.size() && (isNumSysDigit(charAt(i))||charAt(i)==L'_'))
        i++;

    tokenEndIndex=i-1;

    // must be no underscore at the end of number
    if(charAt(tokenEndIndex)==L'_')
        throw IllegalUnderscoreException(lineNumber,getCurrentTokenVal());

}

void LexerLine::getIntNumberToken(
    std::wstring* number,
    NumberToken::NUMBER_TYPE* numType,
    NUM_SYS numSys
){

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
     * The unary minus from Parser may change the numType if the num reached the limits of int or long
    */

    auto isUnsigned=charAt(tokenEndIndex+1)==L'U'||charAt(tokenEndIndex+1)==L'u';
    if(isUnsigned){
        *numType=
        (num<=std::numeric_limits<unsigned int>::max())
        ?NumberToken::UNSIGNED_INT
        :NumberToken::UNSIGNED_LONG;
        tokenEndIndex++; // append 'U' symbol to token
    }
    else{
        *numType=
        (num<=std::numeric_limits<int>::max())
        ?NumberToken::INT
        :(num<=std::numeric_limits<long long>::max())
        ?NumberToken::LONG
        :throw OutOfRangeException(lineNumber,getCurrentTokenVal());
    }

    auto isLong=charAt(tokenEndIndex+1)==L'L'||charAt(tokenEndIndex+1)==L'l';
    if(isLong){
        *numType=
        (isUnsigned)
        ?NumberToken::UNSIGNED_LONG
        :NumberToken::LONG;
        tokenEndIndex++; // append 'L' symbol to token
    }

    wchar_t stopChar=charAt(tokenEndIndex+1);
    
    if(isainalpha(stopChar))
        throw InvalidIdentifierNameException(lineNumber,getCurrentTokenVal()+stopChar); // append stopChar
    
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

SharedLexerToken LexerLine::findIdentifierOrKeywordToken(){
    // Identifiers nad tokens don't start with digits, symbols or spaces
    if(!isainalpha(line[tokenStartIndex]))
        return nullptr;
    
    int i=tokenStartIndex;
    do i++;
    while(isainalpha(line[i])||iswdigit(line[i])); // if next char is alpha or digit add it

    tokenEndIndex=i-1;

    auto val=getCurrentTokenVal();

    auto tokenType=(KeywordToken::iskeyword(val))
    ?LexerToken::KEYWORD_TOKEN:LexerToken::IDENTIFIER_TOKEN;

    auto token=std::make_shared<LexerToken>(tokenType,val);
    return token;
}
#include <cmath>
#include "BinaryExpression.hpp"
#include "BoolExpression.hpp"
#include "SymbolToken.hpp"
#include "number_helper.hpp"
#define wcout std::wcout
#define endl std::endl
#define toint std::stoi
#define tolong std::stol
#define todouble std::stod
#define tofloat std::stof

BinaryExpression::BinaryExpression(SharedIExpression left, SharedLexerToken operation, SharedIExpression right):
left(left),right(right){
    if(
        *operation==SymbolToken::LOGICAL_OR||
        *operation==SymbolToken::LOGICAL_AND||
        *operation==SymbolToken::EQUAL_EQUAL||
        *operation==SymbolToken::NOT_EQUAL||
        *operation==SymbolToken::LESS_EQUAL||
        *operation==SymbolToken::GREATER_EQUAL||
        *operation==SymbolToken::LEFT_ANGLE_BRACKET||
        *operation==SymbolToken::RIGHT_ANGLE_BRACKET||
        *operation==SymbolToken::EXCLAMATION_MARK||
        *operation==SymbolToken::PLUS||
        *operation==SymbolToken::MINUS||
        *operation==SymbolToken::STAR||
        *operation==SymbolToken::SLASH||
        *operation==SymbolToken::MODULO||
        *operation==SymbolToken::POWER
    )
        this->operation=operation;
    else{
        wcout<<L"val: "<<operation->getVal()<<endl;
        std::__throw_invalid_argument("Binary operation must be +, -, *, /, ^, %, >=, <=, ==, !=, && or ||");
    }
}

void BinaryExpression::print(std::wstring tabSize){
    wcout<<tabSize<<"binaryxpression"<<endl;
    auto newTabSize=tabSize+L"\t";
    left->print(newTabSize);
    wcout<<newTabSize<<"Operation"<<endl;
    wcout<<newTabSize+L"\t"<<operation->getVal()<<endl;
    right->print(newTabSize);
}

std::wstring BinaryExpression::evaluate(SharedScope evalScope){
    std::wstring result;
    auto leftRes=left->evaluate(evalScope);
    auto rightRes=right->evaluate(evalScope);

    if(*operation==SymbolToken::LOGICAL_OR){
        result=evaluatelogicalor(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::LOGICAL_AND){
        result=evaluatelogicaland(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::EQUAL_EQUAL){
        result=evaluateequalequal(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::NOT_EQUAL){
        result=evaluatenotequal(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::GREATER_EQUAL){
        result=evaluategreaterequal(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::LESS_EQUAL){
        result=evaluatelessequal(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::RIGHT_ANGLE_BRACKET){
        result=evaluategreater(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::LEFT_ANGLE_BRACKET){
        result=evaluateless(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::PLUS){
        result=evaluateplus(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::MINUS){
        result=evaluateminus(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::STAR){
        result=evaluatestar(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::SLASH){
        result=evaluateslash(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::MODULO){
        result=evaluatemodulo(leftRes,rightRes);
    }
    else if(*operation==SymbolToken::POWER){
        result=evaluatepower(leftRes,rightRes);
    }

    return result;
}

std::wstring BinaryExpression::evaluatelogicalor(std::wstring l, std::wstring r){
    auto res=BoolExpression::boolFromStr(l)||BoolExpression::boolFromStr(r);
    return BoolExpression::strFromBool(res);
}

std::wstring BinaryExpression::evaluatelogicaland(std::wstring l, std::wstring r){
    auto res=BoolExpression::boolFromStr(l)&&BoolExpression::boolFromStr(r);
    return BoolExpression::strFromBool(res);
}

std::wstring BinaryExpression::evaluateequalequal(std::wstring l, std::wstring r){
    auto res=l==r;
    return BoolExpression::strFromBool(res);
}

std::wstring BinaryExpression::evaluatenotequal(std::wstring l, std::wstring r){
    auto res=l!=r;
    return BoolExpression::strFromBool(res);
}

std::wstring BinaryExpression::evaluatelessequal(std::wstring l, std::wstring r){
    auto res=todouble(l)<=todouble(r);
    return BoolExpression::strFromBool(res);
}

std::wstring BinaryExpression::evaluategreaterequal(std::wstring l, std::wstring r){
    auto res=todouble(l)>=todouble(r);
    return BoolExpression::strFromBool(res);
}

std::wstring BinaryExpression::evaluateless(std::wstring l, std::wstring r){
    auto res=todouble(l)<todouble(r);
    return BoolExpression::strFromBool(res);
}

std::wstring BinaryExpression::evaluategreater(std::wstring l, std::wstring r){
    auto res=todouble(l)>todouble(r);
    return BoolExpression::strFromBool(res);
}

std::wstring BinaryExpression::evaluateplus(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)+todouble(r));
    }
    else return l.append(r);
}

std::wstring BinaryExpression::evaluateminus(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)-todouble(r));
    }
    return L"";
}

std::wstring BinaryExpression::evaluatestar(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)*todouble(r));
    }
    return L"";
}

std::wstring BinaryExpression::evaluateslash(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)/todouble(r));
    }
    return L"";
}

std::wstring BinaryExpression::evaluatemodulo(std::wstring l, std::wstring r){
    if(isint(l)&&isint(r)){
        return std::to_wstring(toint(l)%toint(r));
    }
    return L"";
}

std::wstring BinaryExpression::evaluatepower(std::wstring l, std::wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(pow(todouble(l),todouble(r)));
    }
    return L"";
}
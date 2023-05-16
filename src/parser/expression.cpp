#include <iostream>
#include <vector>
#include <cmath>
#include "symboltoken.hpp"
#include "expression.hpp"
#include "number_helper.hpp"
#include "string_helper.hpp"
#define wcout std::wcout
#define endl std::endl
#define toint std::stoi
#define tolong std::stol
#define todouble std::stod
#define tofloat std::stof

numberexpression::numberexpression(wstring &val):val(val){}

void numberexpression::print(wstring &tabsize){
    wcout<<tabsize<<"numberexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<val<<endl;
}

void binaryexpression::print(wstring &tabsize){
    wcout<<tabsize<<"binaryxpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    left->print(newtabsize);
    wcout<<newtabsize<<"Operation"<<endl;
    wcout<<newtabsize+L"\t"<<operation.getval()<<endl;
    right->print(newtabsize);
}

binaryexpression::binaryexpression(expression* left, lexertoken &operation, expression* right):
left(left),right(right){
    if(
        operation==symboltoken::PLUS||
        operation==symboltoken::MINUS||
        operation==symboltoken::STAR||
        operation==symboltoken::SLASH||
        operation==symboltoken::MODULO||
        operation==symboltoken::POWER||
        operation==symboltoken::EXCLAMATION_MARK||
        operation==symboltoken::GREATER_EQUAL||
        operation==symboltoken::LESS_EQUAL||
        operation==symboltoken::EQUAL_EQUAL||
        operation==symboltoken::NOT_EQUAL||
        operation==symboltoken::LOGICAL_AND||
        operation==symboltoken::LOGICAL_OR
    )
        this->operation=operation;
    else{
        wcout<<L"val: "<<operation.getval();
        std::__throw_invalid_argument("Binary operation must be +, -, *, /, ^, %, >=, <=, ==, !=, && or ||");
    }
}

variableaccessexpression::variableaccessexpression(wstring &name):name(name){}

void variableaccessexpression::print(wstring &tabsize){
    wcout<<tabsize<<"variableaccessexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<name<<endl;
}

funcallexpression::
funcallexpression(wstring &funname, std::vector<expression*>* argsexpressions):
funname(funname),argsexpressions(argsexpressions){}

void funcallexpression::print(wstring &tabsize){
    wcout<<tabsize<<"funcallexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<funname<<endl;
    for(auto ex:*argsexpressions){
        ex->print(newtabsize);
    }
}

wstring funcallexpression::evaluate(){
    return L"";
}

wstring variableaccessexpression::evaluate(){
    return L"";
}

wstring numberexpression::evaluate(){
    return val;
}

wstring binaryexpression::evaluate(){
    wstring result;
    auto leftRes=left->evaluate();
    auto rightRes=right->evaluate();

    if(operation==symboltoken::PLUS){
        result=evaluateplus(leftRes,rightRes);
    }
    else if(operation==symboltoken::MINUS){
        result=evaluateminus(leftRes,rightRes);
    }
    else if(operation==symboltoken::STAR){
        result=evaluatestar(leftRes,rightRes);
    }
    else if(operation==symboltoken::SLASH){
        result=evaluateslash(leftRes,rightRes);
    }
    else if(operation==symboltoken::MODULO){
        result=evaluatemodulo(leftRes,rightRes);
    }
    else if(operation==symboltoken::POWER){
        result=evaluatepower(leftRes,rightRes);
    }

    return result;
}

wstring binaryexpression::evaluateplus(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)+todouble(r));
    }
    else return r+l;
}

wstring binaryexpression::evaluateminus(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)-todouble(r));
    }
    return L"";
}

wstring binaryexpression::evaluatestar(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)*todouble(r));
    }
    return L"";
}

wstring binaryexpression::evaluateslash(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(todouble(l)/todouble(r));
    }
    return L"";
}

wstring binaryexpression::evaluatemodulo(wstring l, wstring r){
    if(isint(l)&&isint(r)){
        return std::to_wstring(toint(l)%toint(r));
    }
    return L"";
}

wstring binaryexpression::evaluatepower(wstring l, wstring r){
    if(isnum(l)&&isnum(r)){
        return std::to_wstring(pow(todouble(l),todouble(r)));
    }
    return L"";
}
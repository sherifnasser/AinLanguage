#include "symboltoken.hpp"
#include "expression.hpp"
#define wcout std::wcout
#define endl std::endl

numberexpression::numberexpression(wstring &val):val(val){}

void numberexpression::print(wstring &tabsize){
    wcout<<tabsize<<"numberexpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    wcout<<newtabsize<<val<<endl;
}

void binarymathxpression::print(wstring &tabsize){
    wcout<<tabsize<<"binarymathxpression"<<endl;
    auto newtabsize=tabsize+L"\t";
    left->print(newtabsize);
    wcout<<newtabsize<<"Operation"<<endl;
    wcout<<newtabsize+L"\t"<<operation.getval()<<endl;
    right->print(newtabsize);
}

binarymathxpression::binarymathxpression(expression* left, lexertoken &operation, expression* right):
left(left),right(right){
    if(
        operation==symboltoken::PLUS||
        operation==symboltoken::MINUS||
        operation==symboltoken::STAR||
        operation==symboltoken::SLASH||
        operation==symboltoken::MODULO||
        operation==symboltoken::POWER
    )
        this->operation=operation;
    else{
        wcout<<L"val: "<<operation.getval();
        std::__throw_invalid_argument("Math operation must be +, -, *, /, ^ or %");
    }
}
#include <vector>
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
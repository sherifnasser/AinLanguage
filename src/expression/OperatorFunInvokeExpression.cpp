#include "OperatorFunInvokeExpression.hpp"
#include "FunctionNotFoundException.hpp"
#include "LexerToken.hpp"
#include "NonStaticFunInvokeExpression.hpp"
#include "FunScope.hpp"
#include "FunDecl.hpp"
#include "Type.hpp"
#include "ClassScope.hpp"
#include "FunParam.hpp"

OperatorFunInvokeExpression::OperatorFunInvokeExpression(
    int lineNumber,
    std::wstring opName,
    SharedVector<SharedIExpression> args,
    SharedIExpression inside
):
NonStaticFunInvokeExpression(
    lineNumber,
    opName,
    args,
    inside
){}

std::vector<std::wstring> OperatorFunInvokeExpression::prettyPrint(){

    auto superPrints=NonStaticFunInvokeExpression::prettyPrint();

    auto lineNumStr=std::to_wstring(lineNumber);

    superPrints[0]=L"\033[36;1mOperatorFunInvokeExpression \'"+funName+L"\' at "+lineNumStr+L"\033[0m";

    return superPrints;
}

void OperatorFunInvokeExpression::check(SharedBaseScope checkScope){

    NonStaticFunInvokeExpression::check(checkScope);

    if(*this->fun->getDecl()->isOperator)
        return;
    
    // TODO: make trace more readable
    auto trace=
        inside->getReturnType()->getClassScope()->getName()+
        L"::"+checkScope->getName()+L"("+std::to_wstring(lineNumber)+L")";

    auto params=std::make_shared<std::vector<SharedFunParam>>();
    for(auto arg:*args){
        arg->check(checkScope);
        auto argType=arg->getReturnType();
        params->push_back(
            std::make_shared<FunParam>(nullptr,argType)
        );
    }
    auto decl=FunDecl(
        std::make_shared<std::wstring>(funName),
        nullptr,
        std::make_shared<bool>(false),
        params
    ).toString();
    
    throw FunctionNotFoundException(trace,decl);
}

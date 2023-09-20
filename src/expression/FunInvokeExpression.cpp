#include "FunInvokeExpression.hpp"
#include "BaseScope.hpp"
#include "FunDecl.hpp"
#include "FunParam.hpp"
#include "FunScope.hpp"
#include "ClassScope.hpp"
#include "FileScope.hpp"
#include "FunctionNotFoundException.hpp"
#include "PackageScope.hpp"
#include "SharedPtrTypes.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

FunInvokeExpression::FunInvokeExpression(int lineNumber,std::wstring funName, SharedVector<SharedIExpression> args)
    : IExpression(lineNumber,nullptr),
      funName(funName),
      args(args){}

SharedIValue FunInvokeExpression::evaluate(){
    auto argValues=std::make_shared<std::map<std::wstring,SharedIValue>>();
    auto params=this->fun->getDecl()->params;
    for(int i=0;i<args->size();i++){
        auto argValue=(*args)[i]->evaluate();
        (*argValues)[*params->at(i)->name]=argValue;
    }

    return this->fun->invoke(argValues);
}

std::wstring FunInvokeExpression::getFunName()const{
    return funName;
}

SharedVector<SharedIExpression> FunInvokeExpression::getArgs()const{
    return args;
}
void FunInvokeExpression::setFun(SharedFunScope fun){
    this->fun=fun;
}

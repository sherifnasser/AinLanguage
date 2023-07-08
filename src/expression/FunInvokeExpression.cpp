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

std::vector<std::wstring> FunInvokeExpression::prettyPrint(){
    auto prints=std::vector<std::wstring>();
    auto lineNumStr=std::to_wstring(lineNumber);
    prints.push_back(L"FunExpression \'"+funName+L"\' at "+lineNumStr);

    for(int i=0;i<args->size();i++){
        auto argPrints=args->at(i)->prettyPrint();
        
        argPrints[0]=
            ((i==args->size()-1)?L"└──":L"├──")+argPrints[0];

        for(int j=1;j<argPrints.size();j++){
            argPrints[j]=
                ((i==args->size()-1)?L"    ":L"│   ")+argPrints[j];
        }

        prints.insert(prints.end(),argPrints.begin(),argPrints.end());
    }
    return prints;
}

SharedIValue FunInvokeExpression::evaluate() {
    auto argValues=std::make_shared<std::map<std::wstring,SharedIValue>>();
    auto params=this->fun->getDecl()->params;
    for(int i=0;i<args->size();i++){
        auto argValue=(*args)[i]->evaluate();
        (*argValues)[*params->at(0)->name]=argValue;
    }

    return this->fun->invoke(argValues);
}

void FunInvokeExpression::check(SharedBaseScope checkScope){
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
    );

    auto containingClassScope=BaseScope::getContainingClass(checkScope);
    if(containingClassScope){
        // TODO
    }

    auto containingFileScope=BaseScope::getContainingFile(checkScope);
    if(containingFileScope){
        auto privateFun=containingFileScope->findPrivateFunction(decl.toString());
        if(privateFun){
            this->fun=privateFun;
        }

        auto package=BaseScope::toPackageScope(containingFileScope->getParentScope());
        
        for(auto file:package->getFiles()){
            auto publicFun=file.second->findPublicFunction(decl.toString());
            if(publicFun){
                this->fun=publicFun;
                this->returnType=fun->getReturnType();
                break;
            }
        }
        
        if(!this->fun){
            // TODO: make trace more readable
            auto trace=
            containingFileScope->getName()+
            L"::"+checkScope->getName()+L"("+std::to_wstring(lineNumber)+L")";
            throw FunctionNotFoundException(trace,decl.toString());
        }
    }
}



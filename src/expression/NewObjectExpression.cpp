#include "NewObjectExpression.hpp"
#include "AinException.hpp"
#include "FileScope.hpp"
#include "FunDecl.hpp"
#include "FunInvokeExpression.hpp"
#include "FunParam.hpp"
#include "ConstructorScope.hpp"
#include "FunctionNotFoundException.hpp"
#include "IExpression.hpp"
#include "KeywordToken.hpp"
#include "SharedPtrTypes.hpp"
#include "ClassScope.hpp"
#include "Type.hpp"
#include <memory>
#include <string>
#include <vector>

NewObjectExpression::NewObjectExpression(
    int lineNumber,
    SharedType type,
    SharedVector<SharedIExpression> args
):IExpression(lineNumber,type),args(args){}

SharedIValue NewObjectExpression::evaluate(){
    auto argValues=std::make_shared<std::map<std::wstring,SharedIValue>>();
    auto params=this->constructor->getDecl()->params;
    for(int i=0;i<args->size();i++){
        auto argValue=(*args)[i]->evaluate();
        (*argValues)[*params->at(i)->name]=argValue;
    }

    return this->constructor->invoke(argValues);
}

void NewObjectExpression::check(SharedBaseScope checkScope){
    auto params=std::make_shared<std::vector<SharedFunParam>>();
    for(auto arg:*args){
        arg->check(checkScope);
        auto argType=arg->getReturnType();
        params->push_back(
            std::make_shared<FunParam>(nullptr,argType)
        );
    }
    auto decl=FunDecl(
        std::make_shared<std::wstring>(KeywordToken::NEW.getVal()),
        returnType,
        std::make_shared<bool>(false),
        params
    ).toString();
    
    auto containingClassScope=BaseScope::getContainingClass(checkScope);
    auto returnClassScope=returnType->getClassScope();

    if(containingClassScope==returnClassScope){
        auto privateConstructor=returnClassScope->findPrivateConstructor(decl);

        if(privateConstructor){
            this->constructor=privateConstructor;
            return;
        }
    }

    // TODO: check for protected constructor if parent class of checkScope is child of object class scope

    // TODO: check for protected constructors

    auto publicConstructor=returnClassScope->findPublicConstructor(decl);
    if(publicConstructor){
        this->constructor=publicConstructor;
        return;
    }
    
    auto trace=
        BaseScope::getContainingFile(checkScope)->getName()+
        L"::"+checkScope->getName()+L"("+std::to_wstring(lineNumber)+L")";

    throw FunctionNotFoundException(
        trace,
        decl+L" للنوع "+AinException::betweenAngleBrackets(*returnType->getName())
    );


}

SharedVector<SharedIExpression> NewObjectExpression::getArgs()const{
    return args;
}
#include "NonStaticFunInvokeExpression.hpp"
#include "BaseScope.hpp"
#include "FileScope.hpp"
#include "FunctionNotFoundException.hpp"
#include "SharedPtrTypes.hpp"
#include "Type.hpp"
#include "ClassScope.hpp"
#include "FunDecl.hpp"
#include "FunScope.hpp"
#include "CannotAccessPrivateFunctionException.hpp"
#include "IValue.hpp"
#include "FunParam.hpp"

NonStaticFunInvokeExpression::NonStaticFunInvokeExpression(
    int lineNumber,
    std::wstring funName,
    SharedVector<SharedIExpression> args,
    SharedIExpression inside
)
    : IExpression(lineNumber,nullptr),
      funName(funName),
      args(args),
      inside(inside){}

std::vector<std::wstring> NonStaticFunInvokeExpression::prettyPrint(){
    auto prints=std::vector<std::wstring>();
    auto lineNumStr=std::to_wstring(lineNumber);
    prints.push_back(L"NonStaticFunInvokeExpression \'"+funName+L"\' at "+lineNumStr);

    auto insidePrints=inside->prettyPrint();
    
    insidePrints[0]=
    ((args->size()==0)?L"└──":L"├──")+
    (L"\033[1;33m"+insidePrints[0]+L"\033[0m");

    for(int i=1;i<insidePrints.size();i++){   
        insidePrints[i]=
            ((args->size()==0)?L"    ":L"│   ")+insidePrints[i];
    }

    prints.insert(prints.end(),insidePrints.begin(),insidePrints.end());

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

SharedIValue NonStaticFunInvokeExpression::evaluate(){
    
    auto insideVal=inside->evaluate();
    
    insideVal->linkWithClass();

    auto argValues=std::make_shared<std::map<std::wstring,SharedIValue>>();

    auto params=this->fun->getDecl()->params;
    for(int i=0;i<args->size();i++){
        auto argValue=(*args)[i]->evaluate();
        (*argValues)[*params->at(i)->name]=argValue;
    }

    auto val=this->fun->invoke(argValues);

    insideVal->unlinkWithClass();

    return val;
}

void NonStaticFunInvokeExpression::check(SharedBaseScope checkScope){

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

    inside->check(checkScope);
    auto insideType=inside->getReturnType();
    auto insideClassScope=insideType->getClassScope();

    auto publicFun=insideClassScope->findPublicFunction(decl);

    if(publicFun){
        this->fun=publicFun;
        this->returnType=fun->getReturnType();
        return;
    }

    auto privateFun=insideClassScope->findPrivateFunction(decl);

    // TODO: make trace more readable
    auto trace=
        BaseScope::getContainingFile(checkScope)->getName()+
        L"::"+checkScope->getName()+L"("+std::to_wstring(lineNumber)+L")";

    if(!privateFun)
        throw FunctionNotFoundException(trace,insideClassScope->getName()+L"::"+decl);
    
    if(insideClassScope!=BaseScope::getContainingClass(checkScope))
        throw CannotAccessPrivateFunctionException(trace,decl);
    
    this->fun=publicFun;
    this->returnType=fun->getReturnType();
    
}

NonStaticFunInvokeExpression::~NonStaticFunInvokeExpression(){}

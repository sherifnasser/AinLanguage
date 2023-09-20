#include "NewObjectExpression.hpp"
#include "AinException.hpp"
#include "FileScope.hpp"
#include "FunDecl.hpp"
#include "FunInvokeExpression.hpp"
#include "FunParam.hpp"
#include "ConstructorScope.hpp"
#include "FunctionNotFoundException.hpp"
#include "IExpression.hpp"
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

SharedVector<SharedIExpression> NewObjectExpression::getArgs()const{
    return args;
}
void NewObjectExpression::setConstructor(SharedConstructorScope constructor){
    this->constructor=constructor;
}

#include "FunScope.hpp"
#include "ClassScope.hpp"
#include "FunDecl.hpp"
#include "OperatorFunctions.hpp"
#include "SharedPtrTypes.hpp"
#include "FunParam.hpp"
#include "StmListScope.hpp"
#include "Type.hpp"
#include "Variable.hpp"
#include "IStatement.hpp"
#include "FunDecl.hpp"
#include <string>
#include "InvalidOperatorFunDeclarationException.hpp"

FunScope::FunScope(
    SharedBaseScope parentScope,
    SharedFunDecl decl
):StmListScope(*decl->name,parentScope),decl(decl)
{}

SharedIValue FunScope::invoke(SharedMap<std::wstring, SharedIValue> params){

    for(auto local:*locals){
        auto varName=local.first;
        auto var=local.second;
        var->pushNewValue();
        auto paramIt=params->find(varName);
        if(paramIt!=params->end()){
            var->setValue(paramIt->second);
        }
    }

    for(auto stm:*stmList){
        stm->run();
        if(this->returnValue)
            break;
    }

    for(auto local:*locals){
        local.second->popLastValue();
    }

    auto retVal=this->returnValue;

    this->returnValue=nullptr;

    return retVal;
}

SharedType FunScope::getReturnType(){
    return this->decl->returnType;
}

SharedFunDecl FunScope::getDecl(){
    return this->decl;
}

void FunScope::setReturnValue(SharedIValue returnValue){
    this->returnValue=returnValue;
}

SharedIValue FunScope::getReturnValue(){
    return this->returnValue;
}

void FunScope::check(){

    if(*this->decl->isOperator)
        doOperatorFunChecks();

    StmListScope::check();
}

void FunScope::doOperatorFunChecks(){

    checkOperatorFunParamsSize();

    checkOperatorFunReturnType();
    
}

void FunScope::checkOperatorFunParamsSize(){
    
    auto paramsSize=this->decl->params->size();
    auto opName=this->name;

    auto isBinOp=
        opName==OperatorFunctions::PLUS_NAME
        ||
        opName==OperatorFunctions::MINUS_NAME
        ||
        opName==OperatorFunctions::TIMES_NAME
        ||
        opName==OperatorFunctions::DIV_NAME
        ||
        opName==OperatorFunctions::MOD_NAME
        ||
        opName==OperatorFunctions::POW_NAME
    ;

    if(isBinOp&&paramsSize!=1)
        throw InvalidOperatorFunDeclarationException(L"عدد المعاملات غير صالح لدالة "+opName);

    auto isUnaryOp=
        opName==OperatorFunctions::UNARY_PLUS_NAME
        ||
        opName==OperatorFunctions::UNARY_MINUS_NAME
        ||
        opName==OperatorFunctions::NOT_NAME
        ||
        opName==OperatorFunctions::INC_NAME
        ||
        opName==OperatorFunctions::DEC_NAME
    ;

    if(isUnaryOp&&paramsSize!=0)
        throw InvalidOperatorFunDeclarationException(L"عدد المعاملات غير صالح لدالة "+opName);

}

void FunScope::checkOperatorFunReturnType(){
    
    auto opName=this->name;

    auto returnType=this->decl->returnType;

    if(opName==OperatorFunctions::COMPARE_TO_NAME&&*returnType->getName()!=*Type::INT_NAME)
        throw InvalidOperatorFunDeclarationException(L"دالة قارن_مع يجب أن ترجع قيمة من نوع صحيح.");

    if(opName==OperatorFunctions::EQUALS_NAME&&*returnType->getName()!=*Type::BOOL_NAME)
        throw InvalidOperatorFunDeclarationException(L"دالة يساوي يجب أن ترجع قيمة من نوع منطقي.");
    
    auto parentClass=getContainingClass(this->parentScope);
    if(
        (opName==OperatorFunctions::INC_NAME||opName==OperatorFunctions::DEC_NAME)
        &&
        returnType->getClassScope()!=parentClass
    )
        throw InvalidOperatorFunDeclarationException(
            L"دالة "+opName+
            L" يجب أن ترجع قيمة من نفس نوع "+parentClass->getName()
        );
    
}

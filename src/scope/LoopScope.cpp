#include "LoopScope.hpp"
#include "FunScope.hpp"
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"

LoopScope::LoopScope(SharedBaseScope parentScope):
    StmListScope(L"حلقة_تكرارية",parentScope),
    containingFunScope(BaseScope::getContainingFun(parentScope)),
    toBreak(false),toContinue(false)
{}


bool LoopScope::isBreak(){
    return this->toBreak;
}

bool LoopScope::isContinue(){
    return this->toContinue;
}

bool LoopScope::isReturn(){
    return this->containingFunScope->getReturnValue()!=nullptr;
}

void LoopScope::makeBreak(){
    this->toBreak=true;
}

void LoopScope::makeContinue(){
    this->toContinue=true;
}

void LoopScope::resetBreak(){
    this->toBreak=false;
}

void LoopScope::resetContinue(){
    this->toContinue=false;
}

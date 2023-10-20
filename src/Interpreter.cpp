#include "Interpreter.hpp"
#include "ArrayNegativeCapacityException.hpp"
#include "ArrayValue.hpp"
#include "BoolValue.hpp"
#include "FunDecl.hpp"
#include "IntValue.hpp"
#include "ObjectValue.hpp"
#include "OperatorFunInvokeExpression.hpp"
#include "SetOperatorExpression.hpp"
#include "SharedPtrTypes.hpp"
#include "UnitValue.hpp"
#include "Variable.hpp"
#include "FunParam.hpp"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

void Interpreter::push(SharedIValue val){
    valuesStack.push(val);
}

SharedIValue Interpreter::top(){
    if(valuesStack.empty())
        throw;
    
    return valuesStack.top();
}

SharedIValue Interpreter::pop(){
    if(valuesStack.empty())
        throw;

    auto val=valuesStack.top();

    valuesStack.pop();

    return val;
}

void Interpreter::runStmList(StmListScope* scope){
    for(auto stm:*scope->getStmList()){
        stm->accept(this);
        if(funReturn||loopBreak||loopContinue)
            break;
    }
}

void Interpreter::initStmListLocals(StmListScope* scope){
    
    auto locals=scope->getLocals();

    for(auto localIt=locals->begin();localIt!=locals->end();localIt++){
        auto varName=localIt->first;
        auto var=localIt->second;
        var->pushNewValue();
    }
}

void Interpreter::invokeNonStaticFun(NonStaticFunInvokeExpression* ex){

    auto insideVal=pop();

    insideVal->linkWithClass();

    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    ex->getFun()->accept(this);

    insideVal->unlinkWithClass();
}

std::shared_ptr<ArrayValue> Interpreter::initMultiDArray(
    int capIndex,
    int capacitiesSize,
    int capacities[],
    SharedType type
){
    auto cap=capacities[capIndex];
    
    auto array=std::make_shared<ArrayValue>(type,cap);
    
    if(capIndex==capacitiesSize-1)
        return array;
    
    auto arrayType=type->asArray()->getType();
    auto arrayVal=array->getValue();
    auto childrenCapIndex=capIndex+1;
    auto childrenCap=capacities[childrenCapIndex];
    for(int i=0;i<childrenCap;i++){
        arrayVal[i]=initMultiDArray(
            childrenCapIndex,
            capacitiesSize,
            capacities,
            arrayType
        );
    }

    return array;

}

Interpreter::Interpreter():
funReturn(false),loopBreak(false),loopContinue(false){}

Interpreter::Interpreter(Assigner* assigner):assigner(assigner){}

Interpreter::Assigner::Assigner(Interpreter* interpreter)
:interpreter(interpreter){}

void Interpreter::Assigner::visit(VarAccessExpression* ex){
    if(!assign){
        ex->accept(interpreter);
    }else{
        ex->getVar()->setValue(interpreter->pop());
    }
    assign=!assign;
}

void Interpreter::Assigner::visit(NonStaticVarAccessExpression* ex){
    if(!assign){
        ex->getInside()->accept(interpreter);
        auto var=interpreter->topAs<ObjectValue>();
        interpreter->push(var->findPropertyValue(ex->getVarName()));
    }else{
        auto val=interpreter->pop();
        auto var=interpreter->popAs<ObjectValue>();
        var->assignProperty(ex->getVarName(),val);
    }
    assign=!assign;
}

void Interpreter::Assigner::visit(OperatorFunInvokeExpression* ex){
    interpreter->invokeNonStaticFun(ex);
}

void Interpreter::visit(PackageScope* scope){
    for(auto packageIterator:scope->getPackages()){
        packageIterator.second->accept(this);
    }
    for(auto fileIterator:scope->getFiles()){
        fileIterator.second->accept(this);
    }
}

void Interpreter::visit(FileScope* scope){
    for(auto varIt:*scope->getPublicVariables()){
        varIt.second->pushNewValue();
    }
    for(auto varIt:*scope->getPrivateVariables()){
        varIt.second->pushNewValue();
    }

    scope->getGlobalVarsInitStmList()->accept(this);
}

void Interpreter::visit(ClassScope* scope){

    for(auto varIt:*scope->getPrivateVariables()){
        varIt.second->pushNewValue();
    }
    for(auto varIt:*scope->getPublicVariables()){
        varIt.second->pushNewValue();
    }

    scope->getVarsInitStmList()->accept(this);
}

void Interpreter::visit(FunScope* scope){

    auto decl=scope->getDecl();
    auto isConstructor=decl->isConstructor();

    if(isConstructor)
        decl->returnType->getClassScope()->accept(this);

    auto locals=scope->getLocals();

    initStmListLocals(scope);

    auto params=decl->params;
    for(auto paramIt=params->rbegin();paramIt!=params->rend();paramIt++){
        (*locals)[*paramIt->get()->name]->setValue(pop());
    }

    for(auto stm:*scope->getStmList()){
        stm->accept(this);
        if(funReturn)
            break;
    }

    for(auto local:*locals){
        local.second->popLastValue();
    }

    if(!funReturn&&!isConstructor)
        push(std::make_shared<UnitValue>());
    
    funReturn=false;

    if(!isConstructor)
        return;

    auto properties=std::make_shared<std::unordered_map<std::wstring, SharedIValue>>();

    auto classScope=decl->returnType->getClassScope();

    for(auto varIt:*classScope->getPrivateVariables()){
        (*properties)[varIt.first]=varIt.second->getValue();
        varIt.second->popLastValue();
    }
    for(auto varIt:*classScope->getPublicVariables()){
        (*properties)[varIt.first]=varIt.second->getValue();
        varIt.second->popLastValue();
    }

    push(std::make_shared<ObjectValue>(decl->returnType,properties));

}

void Interpreter::visit(BuiltInFunScope* scope){
    auto args=std::make_shared<std::unordered_map<std::wstring, SharedIValue>>();
    auto params=scope->getDecl()->params;
    for(auto paramIt=params->rbegin();paramIt!=params->rend();paramIt++){
        (*args)[*paramIt->get()->name]=pop();
    }
    push(scope->invoke(args));
}

void Interpreter::visit(LoopScope* scope){
    initStmListLocals(scope);
    runStmList(scope);
}

void Interpreter::visit(StmListScope* scope){
    initStmListLocals(scope);
    runStmList(scope);
}

void Interpreter::visit(VarStm* stm){
    stm->getEx()->accept(this);
    stm->getVar()->setValue(pop());
}

void Interpreter::visit(AssignStatement* stm){
    stm->getLeft()->accept(assigner);
    pop();
    stm->getRight()->accept(this);
    stm->getLeft()->accept(assigner);
}

void Interpreter::visit(AugmentedAssignStatement* stm){
    
    stm->getLeft()->accept(assigner);
    auto leftVal=pop();

    stm->getRight()->accept(this);
    auto rightVal=top();

    leftVal->linkWithClass();
    stm->getOpFun()->accept(this);
    leftVal->unlinkWithClass();
    
    stm->getLeft()->accept(assigner);
}

void Interpreter::visit(IfStatement* stm){
    SharedStmListScope scope;

    stm->getIfCondition()->accept(this);

    if(popAs<BoolValue>()->getValue()){
        scope=stm->getIfScope();
    }
    else if(auto elseScope=stm->getElseScope()){
        scope=elseScope;
    }
    else return;
    
    scope->accept(this);
}

void Interpreter::visit(WhileStatement* stm){
    
    while(true){
        stm->getCondition()->accept(this);

        if(!popAs<BoolValue>()->getValue())
            break;
        
        stm->getLoopScope()->accept(this);

        if(loopContinue)
            loopContinue=false;

        if(loopBreak){
            loopBreak=false;
            break;
        }

        if(funReturn)
            break;
        
    }
}

void Interpreter::visit(DoWhileStatement* stm){
    do{
        stm->getLoopScope()->accept(this);

        if(loopContinue)
            loopContinue=false;

        if(loopBreak){
            loopBreak=false;
            break;
        }

        if(funReturn)
            break;
        
        stm->getCondition()->accept(this);

        if(!popAs<BoolValue>()->getValue())
            break;
        
    }
    while(true);
}

void Interpreter::visit(BreakStatement* stm){
    loopBreak=true;
}

void Interpreter::visit(ContinueStatement* stm){
    loopContinue=true;
}

void Interpreter::visit(ReturnStatement* stm){
    stm->getEx()->accept(this);
    funReturn=true;
}

void Interpreter::visit(ExpressionStatement* stm){
    stm->getEx()->accept(this);
    pop();
}

void Interpreter::visit(VarAccessExpression* ex){
    push(ex->getVar()->getValue());
}

void Interpreter::visit(FunInvokeExpression* ex){
    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    ex->getFun()->accept(this);
}

void Interpreter::visit(NewObjectExpression* ex){
    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    ex->getConstructor()->accept(this);
}

void Interpreter::visit(NewArrayExpression* ex){
    auto capacitiesExpressions=ex->getCapacities();

    auto capacitiesSize=capacitiesExpressions.size();

    int capacities[capacitiesSize];

    for(int i=0;i<capacitiesSize;i++){
        capacitiesExpressions[i]->accept(this);

        auto cap=popAs<IntValue>()->getValue();

        if(cap<0)
            throw ArrayNegativeCapacityException(cap);

        capacities[i]=cap;
    }

    // Recursion could cause stack overflow
    std::shared_ptr<ArrayValue> arrayVal=initMultiDArray(
        0,
        capacitiesSize,
        capacities,
        ex->getReturnType()
    );
    
    push(arrayVal);
}

void Interpreter::visit(LiteralExpression* ex){
    push(ex->getValue());
}

void Interpreter::visit(UnitExpression* ex){
    push(std::make_shared<UnitValue>());
}

void Interpreter::visit(LogicalExpression* ex){
    ex->getLeft()->accept(this);
    auto leftVal=popAs<BoolValue>();
    auto leftBoolVal=leftVal->getValue();
    auto op=ex->getLogicalOp();
    if(
        leftBoolVal&&op==LogicalExpression::Operation::OR
        ||
        !leftBoolVal&&op==LogicalExpression::Operation::AND
    ){
        push(leftVal);
        return;
    }
    ex->getRight()->accept(this);
}

void Interpreter::visit(NonStaticVarAccessExpression* ex){
    ex->getInside()->accept(this);
    auto propVal=popAs<ObjectValue>()->findPropertyValue(ex->getVarName());
    push(propVal);
}

void Interpreter::visit(NonStaticFunInvokeExpression* ex){
    ex->getInside()->accept(this);
    invokeNonStaticFun(ex);
}

void Interpreter::visit(OperatorFunInvokeExpression* ex){
    auto op=ex->getOp();

    if(
        op==OperatorFunInvokeExpression::Operator::PRE_INC
        ||
        op==OperatorFunInvokeExpression::Operator::PRE_DEC
        ||
        op==OperatorFunInvokeExpression::Operator::POST_INC
        ||
        op==OperatorFunInvokeExpression::Operator::POST_DEC
    ){

        ex->getInside()->accept(assigner);

        auto oldVal=top();
        
        invokeNonStaticFun(ex);

        auto newVal=top();

        ex->getInside()->accept(assigner);
        
        switch(op){
            case OperatorFunInvokeExpression::Operator::PRE_INC:
            case OperatorFunInvokeExpression::Operator::PRE_DEC:
                push(newVal);
                break;
            case OperatorFunInvokeExpression::Operator::POST_INC:
            case OperatorFunInvokeExpression::Operator::POST_DEC:
                push(oldVal);
                break;
            default:break;
        }

        return;
    }

    ex->getInside()->accept(this);
    invokeNonStaticFun(ex);
    switch(op){
        case OperatorFunInvokeExpression::Operator::NOT_EQUAL:{
            auto val=popAs<BoolValue>()->getValue();
            push(std::make_shared<BoolValue>(!val));
            break;
        }
        case OperatorFunInvokeExpression::Operator::LESS:{
            auto val=popAs<IntValue>()->getValue();
            push(std::make_shared<BoolValue>(val<0));
            break;
        }
        case OperatorFunInvokeExpression::Operator::LESS_EQUAL:{
            auto val=popAs<IntValue>()->getValue();
            push(std::make_shared<BoolValue>(val<=0));
            break;
        }
        case OperatorFunInvokeExpression::Operator::GREATER:{
            auto val=popAs<IntValue>()->getValue();
            push(std::make_shared<BoolValue>(val>0));
            break;
        }
        case OperatorFunInvokeExpression::Operator::GREATER_EQUAL:{
            auto val=popAs<IntValue>()->getValue();
            push(std::make_shared<BoolValue>(val>=0));
            break;
        }
        default:
            break;
    }
}

void Interpreter::visit(SetOperatorExpression* ex){

    auto op=ex->getOp();
    
    ex->getExHasGetOp()->accept(this);
    auto valHasGet=pop();

    ex->getIndexEx()->accept(this);
    auto index=top();

    valHasGet->linkWithClass();
    ex->getExOfGet()->getFun()->accept(this);
    valHasGet->unlinkWithClass();
    auto valueOfGet=pop();

    switch(op){
        case SetOperatorExpression::Operator::PLUS_EQUAL:
        case SetOperatorExpression::Operator::MINUS_EQUAL:
        case SetOperatorExpression::Operator::TIMES_EQUAL:
        case SetOperatorExpression::Operator::DIV_EQUAL:
        case SetOperatorExpression::Operator::MOD_EQUAL:
        case SetOperatorExpression::Operator::POW_EQUAL:
        case SetOperatorExpression::Operator::SHR_EQUAL:
        case SetOperatorExpression::Operator::SHL_EQUAL:
        case SetOperatorExpression::Operator::BIT_AND_EQUAL:
        case SetOperatorExpression::Operator::XOR_EQUAL:
        case SetOperatorExpression::Operator::BIT_OR_EQUAL:{
            push(valueOfGet);
            ex->getValueEx()->accept(this);
        }
        default:break;
    }

    valueOfGet->linkWithClass();
    ex->getFunOfOp()->accept(this);
    valueOfGet->unlinkWithClass();
    auto valueToSet=pop();

    push(index);
    push(valueToSet);

    valHasGet->linkWithClass();
    ex->getFunOfSet()->accept(this);
    valHasGet->unlinkWithClass();

    switch(op){
        case SetOperatorExpression::Operator::PRE_INC:
        case SetOperatorExpression::Operator::PRE_DEC:{
            pop();
            push(index);
            valHasGet->linkWithClass();
            ex->getExOfGet()->getFun()->accept(this);
            valHasGet->unlinkWithClass();
            break;
        }
        case SetOperatorExpression::Operator::POST_INC:
        case SetOperatorExpression::Operator::POST_DEC:{
            pop();
            push(valueOfGet);
            break;
        }
        default:break;
    }
}
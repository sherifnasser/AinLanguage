#include "BuiltInFunScope.hpp"
#include "ArrayNegativeCapacityException.hpp"
#include "ArrayValue.hpp"
#include "BoolValue.hpp"
#include "ArrayClassScope.hpp"
#include "CharValue.hpp"
#include "FunDecl.hpp"
#include "FunScope.hpp"
#include "IValue.hpp"
#include "IntValue.hpp"
#include "Interpreter.hpp"
#include "ObjectValue.hpp"
#include "OperatorFunInvokeExpression.hpp"
#include "OutOfMemoryException.hpp"
#include "RefValue.hpp"
#include "SetOperatorExpression.hpp"
#include "SharedPtrTypes.hpp"
#include "StackOverFlowException.hpp"
#include "StackUnderFlowException.hpp"
#include "Type.hpp"
#include "UnitValue.hpp"
#include "Variable.hpp"
#include "FunParam.hpp"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

void InterpreterV2::push(IValue* val){
    if(++*SP>=STACK_SIZE)
        throw StackOverFlowException();

    stack[*SP]=val;
}

IValue* InterpreterV2::top(){
    if(*SP<0)
        throw StackUnderFlowException();
    
    return stack[*SP];
}

IValue* InterpreterV2::pop(){
    if(*SP<0)
        throw StackUnderFlowException();
    auto val=stack[*SP];
    stack[(*SP)--]=0;
    return val;
}

void InterpreterV2::runStmList(StmListScope* scope){
    for(auto stm:*scope->getStmList()){
        stm->accept(this);
        if(funReturn||loopBreak||loopContinue)
            break;
    }
}

void InterpreterV2::offsetStmListLocals(int size){
    *SP+=size;
}

void InterpreterV2::invokeNonStaticFun(NonStaticFunInvokeExpression* ex){
    push(new RefValue(*BX));

    ex->getInside()->accept(this);

    *BX=popAs<RefValue>()->getAddress();

    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    ex->getFun()->accept(this);

    for(auto arg:*args){
        pop();
    }

    *BX=popAs<RefValue>()->getAddress();

    push(AX); // return value
}

void InterpreterV2::invokeNonStaticBuiltInFun(NonStaticFunInvokeExpression* ex){
    ex->getInside()->accept(this);

    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    switch(args->size()){
        case 2:
            DX=pop();
        case 1:
            CX=pop();
        case 0:
        default:
            AX=pop();
    }

    ex->getFun()->accept(this);

    push(AX); // return value
}

void InterpreterV2::invokeBuiltInOpFun(OperatorFunInvokeExpression* ex){
    
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

        ex->getInside()->accept(lAssigner);

        DX=pop();

        AX=DX;

        ex->getFun()->accept(this);

        push(AX); // push return value to assign it

        ex->getInside()->accept(rAssigner);
        
        switch(op){
            case OperatorFunInvokeExpression::Operator::PRE_INC:
            case OperatorFunInvokeExpression::Operator::PRE_DEC:
                push(AX);
                break;
            case OperatorFunInvokeExpression::Operator::POST_INC:
            case OperatorFunInvokeExpression::Operator::POST_DEC:
                push(DX);
                break;
            default:{}
        }

        return;
    }
    
    ex->getInside()->accept(this);

    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    switch(op){
        case OperatorFunInvokeExpression::Operator::SET_EQUAL:
            DX=pop();   // value arg
        case OperatorFunInvokeExpression::Operator::PLUS:
        case OperatorFunInvokeExpression::Operator::MINUS:
        case OperatorFunInvokeExpression::Operator::TIMES:
        case OperatorFunInvokeExpression::Operator::DIV:
        case OperatorFunInvokeExpression::Operator::MOD:
        case OperatorFunInvokeExpression::Operator::POW:
        case OperatorFunInvokeExpression::Operator::EQUAL_EQUAL:
        case OperatorFunInvokeExpression::Operator::NOT_EQUAL:
        case OperatorFunInvokeExpression::Operator::LESS:
        case OperatorFunInvokeExpression::Operator::LESS_EQUAL:
        case OperatorFunInvokeExpression::Operator::GREATER:
        case OperatorFunInvokeExpression::Operator::GREATER_EQUAL:
        case OperatorFunInvokeExpression::Operator::SHR:
        case OperatorFunInvokeExpression::Operator::SHL:
        case OperatorFunInvokeExpression::Operator::BIT_AND:
        case OperatorFunInvokeExpression::Operator::XOR:
        case OperatorFunInvokeExpression::Operator::BIT_OR:
        case OperatorFunInvokeExpression::Operator::GET:
            CX=pop();   // 2nd operand
        case OperatorFunInvokeExpression::Operator::UNARY_PLUS:
        case OperatorFunInvokeExpression::Operator::UNARY_MINUS:
        case OperatorFunInvokeExpression::Operator::LOGICAL_NOT:
        case OperatorFunInvokeExpression::Operator::BIT_NOT:
            AX=pop();   // 1st operand
            break;
        default:{}
    }

    ex->getFun()->accept(this);

    switch(op){
        case OperatorFunInvokeExpression::Operator::NOT_EQUAL:{
            auto val=dynamic_cast<BoolValue*>(AX)->getValue();
            AX=new BoolValue(!val);
            break;
        }
        case OperatorFunInvokeExpression::Operator::LESS:{
            auto val=dynamic_cast<IntValue*>(AX)->getValue();
            AX=new BoolValue(val<0);
            break;
        }
        case OperatorFunInvokeExpression::Operator::LESS_EQUAL:{
            auto val=dynamic_cast<IntValue*>(AX)->getValue();
            AX=new BoolValue(val<=0);
            break;
        }
        case OperatorFunInvokeExpression::Operator::GREATER:{
            auto val=dynamic_cast<IntValue*>(AX)->getValue();
            AX=new BoolValue(val>0);
            break;
        }
        case OperatorFunInvokeExpression::Operator::GREATER_EQUAL:{
            auto val=dynamic_cast<IntValue*>(AX)->getValue();
            AX=new BoolValue(val>=0);
            break;
        }
        default:
            break;
    }

    push(AX);
}

ArrayValue* InterpreterV2::initMultiDArray(
    int capIndex,
    int capacitiesSize,
    int capacities[],
    SharedType type
){
    // TODO
    /*auto cap=capacities[capIndex];
    
    auto array=new ArrayValue(type,cap);
    
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

    return array;*/

    return nullptr;
}

int InterpreterV2::getAvailableHeapAddress(ClassScope* scope){
    int objSize=scope->getPublicVariables()->size()+scope->getPrivateVariables()->size();
    int heapAddress=HEAP_SIZE;

    for(int i=0;i<HEAP_SIZE;){
        if(auto reservedObj=heap[i]){
            auto reservedObjSize=dynamic_cast<IntValue*>(reservedObj);
            i+=reservedObjSize->getValue()+1;
            continue;
        }
        int j=i;
        int lastValidCell=i+objSize;
        for(;j<=lastValidCell;j++){
            if(heap[j])
                break;
        }
        if(j>lastValidCell){
            heapAddress=i;
            break;
        }
        i=j;
    }

    if(heapAddress>=HEAP_SIZE)
        throw OutOfMemoryException();

    heap[heapAddress]=new IntValue(objSize);

    return heapAddress;
}

InterpreterV2::InterpreterV2():
    BP(new int(0)),
    SP(new int(0)),
    BX(new int(-1)),
    funReturn(false),
    loopBreak(false),
    loopContinue(false)
{}

InterpreterV2::LeftSideAssigner::LeftSideAssigner(InterpreterV2* interpreter)
:interpreter(interpreter){}

void InterpreterV2::LeftSideAssigner::visit(VarAccessExpression* ex){
    ex->accept(interpreter);
}

void InterpreterV2::LeftSideAssigner::visit(NonStaticVarAccessExpression* ex){
    ex->getInside()->accept(interpreter);
    auto ref=interpreter->topAs<RefValue>()->getAddress();
    interpreter->push(
        interpreter->heap[ref+interpreter->offsets[ex->getVar().get()].value]
    );
}

InterpreterV2::RightSideAssigner::RightSideAssigner(InterpreterV2* interpreter)
:interpreter(interpreter){}

void InterpreterV2::RightSideAssigner::visit(VarAccessExpression* ex){
    auto offset=interpreter->offsets[ex->getVar().get()];
    auto mem=(offset.reg==interpreter->BP)?interpreter->stack:interpreter->heap;
    mem[*offset.reg+offset.value]=interpreter->pop();
}

void InterpreterV2::RightSideAssigner::visit(NonStaticVarAccessExpression* ex){
    auto val=interpreter->pop();
    auto ref=interpreter->popAs<RefValue>()->getAddress();
    interpreter->heap[ref+interpreter->offsets[ex->getVar().get()].value]=val;
}

void InterpreterV2::visit(PackageScope* scope){
    // TODO
}

void InterpreterV2::visit(FileScope* scope){

    // TODO: Global variables
    /*
    for(auto varIt:*scope->getPublicVariables()){
        varIt.second->pushNewValue();
    }
    for(auto varIt:*scope->getPrivateVariables()){
        varIt.second->pushNewValue();
    }

    scope->getGlobalVarsInitStmList()->accept(this);*/
}

void InterpreterV2::visit(ClassScope* scope){
    scope->getVarsInitStmList()->accept(this);
}

void InterpreterV2::visit(FunScope* scope){

    push(new IntValue(*BP));

    *BP=*SP;

    auto decl=scope->getDecl();
    auto isConstructor=decl->isConstructor();

    if(isConstructor)
        decl->returnType->getClassScope()->accept(this);

    // locals contains params, so we don't offset params
    auto localsSize=scope->getLocals()->size();
    auto paramsSize=scope->getDecl()->params->size();

    if(localsSize>paramsSize)
        offsetStmListLocals(localsSize-paramsSize);

    for(auto stm:*scope->getStmList()){
        stm->accept(this);
        if(funReturn)
            break;
    }

    if(isConstructor)
        AX=new RefValue(*BX);

    // When return type of a function is unit but it reaches its end, without an explicit return
    else if(!funReturn) 
        AX=new UnitValue;
    
    funReturn=false;

    *SP=*BP;

    *BP=popAs<IntValue>()->getValue();

}

void InterpreterV2::visit(BuiltInFunScope* scope){
    // Built-in functions don't affect BP, so we don't need to push it on the stack

    scope->invokeOnInterpreter(this);

}

void InterpreterV2::visit(LoopScope* scope){
    offsetStmListLocals(scope->getLocals()->size());
    runStmList(scope);
}

void InterpreterV2::visit(StmListScope* scope){
    offsetStmListLocals(scope->getLocals()->size());
    runStmList(scope);
}

void InterpreterV2::visit(VarStm* stm){
    stm->getEx()->accept(this);
    auto offset=offsets[stm->getVar().get()];
    auto mem=(offset.reg==BP)?stack:heap;
    mem[*offset.reg+offset.value]=pop();
}

void InterpreterV2::visit(AssignStatement* stm){
    stm->getLeft()->accept(lAssigner);
    pop();
    stm->getRight()->accept(this);
    stm->getLeft()->accept(rAssigner);
}

void InterpreterV2::visit(AugmentedAssignStatement* stm){

    if(auto isBuiltIn=std::dynamic_pointer_cast<BuiltInFunScope>(stm->getOpFun())){
        stm->getLeft()->accept(lAssigner);
        stm->getRight()->accept(this);
        CX=pop();
        AX=pop();
        stm->getOpFun()->accept(this);
        push(AX);
        stm->getLeft()->accept(rAssigner);
    }else{
        push(new RefValue(*BX));
        stm->getLeft()->accept(lAssigner);
        *BX=popAs<RefValue>()->getAddress();
        stm->getRight()->accept(this);
        stm->getOpFun()->accept(this);
        pop();  // pop right
        push(AX);
        stm->getLeft()->accept(rAssigner);
        *BX=popAs<RefValue>()->getAddress();
    }
    
}

void InterpreterV2::visit(IfStatement* stm){
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

void InterpreterV2::visit(WhileStatement* stm){
    
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

void InterpreterV2::visit(DoWhileStatement* stm){

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
        
    }while(true);
}

void InterpreterV2::visit(BreakStatement* stm){
    loopBreak=true;
}

void InterpreterV2::visit(ContinueStatement* stm){
    loopContinue=true;
}

void InterpreterV2::visit(ReturnStatement* stm){
    stm->getEx()->accept(this);
    AX=pop();
    funReturn=true;
}

void InterpreterV2::visit(ExpressionStatement* stm){
    stm->getEx()->accept(this);
    pop();
}

void InterpreterV2::visit(VarAccessExpression* ex){
    auto offset=offsets[ex->getVar().get()];
    auto memory=(offset.reg==BP)?stack:heap;
    push(memory[*offset.reg+offset.value]);
}

void InterpreterV2::visit(FunInvokeExpression* ex){

    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    ex->getFun()->accept(this);

    for(auto arg:*args){
        pop();
    }

    push(AX); // return value
}

void InterpreterV2::visit(NewObjectExpression* ex){

    int heapAddress=getAvailableHeapAddress(ex->getReturnType()->getClassScope().get());

    push(new RefValue(*BX));

    *BX=heapAddress;

    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    ex->getConstructor()->accept(this);

    for(auto arg:*args){
        pop();
    }

    *BX=popAs<RefValue>()->getAddress();

    push(AX); // return address of object
}

//void InterpreterV2::visit(NewArrayExpression* ex){
    // TODO
    /*auto capacitiesExpressions=ex->getCapacities();

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
    
    push(arrayVal);*/
//d}

void InterpreterV2::visit(LiteralExpression* ex){
    push(ex->getValue().get());
}

void InterpreterV2::visit(UnitExpression* ex){
    push(new UnitValue);
}

void InterpreterV2::visit(LogicalExpression* ex){
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

void InterpreterV2::visit(NonStaticVarAccessExpression* ex){
    ex->getInside()->accept(this);
    AX=pop();
    auto ax=dynamic_cast<RefValue*>(AX)->getAddress();
    push(
        heap[ax+offsets[ex->getVar().get()].value]
    );
}

void InterpreterV2::visit(NonStaticFunInvokeExpression* ex){
    if(auto builtIn=std::dynamic_pointer_cast<BuiltInFunScope>(ex->getFun())){
        invokeNonStaticBuiltInFun(ex);
        return;
    }
    invokeNonStaticFun(ex);
}

void InterpreterV2::visit(OperatorFunInvokeExpression* ex){
    
    if(auto builtIn=std::dynamic_pointer_cast<BuiltInFunScope>(ex->getFun())){
        invokeBuiltInOpFun(ex);
        return;
    }

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
        push(new RefValue(*BX));

        ex->getInside()->accept(lAssigner);

        auto oldVal=pop();

        *BX=dynamic_cast<RefValue*>(oldVal)->getAddress();
        
        ex->getFun()->accept(this);

        *BX=popAs<RefValue>()->getAddress();

        push(AX); // return value

        ex->getInside()->accept(rAssigner);
        
        switch(op){
            case OperatorFunInvokeExpression::Operator::PRE_INC:
            case OperatorFunInvokeExpression::Operator::PRE_DEC:
                push(AX);
                break;
            case OperatorFunInvokeExpression::Operator::POST_INC:
            case OperatorFunInvokeExpression::Operator::POST_DEC:
                push(oldVal);
                break;
            default:break;
        }

        return;
    }

    invokeNonStaticFun(ex);
    switch(op){
        case OperatorFunInvokeExpression::Operator::NOT_EQUAL:{
            auto val=popAs<BoolValue>()->getValue();
            push(new BoolValue(!val));
            break;
        }
        case OperatorFunInvokeExpression::Operator::LESS:{
            auto val=popAs<IntValue>()->getValue();
            push(new BoolValue(val<0));
            break;
        }
        case OperatorFunInvokeExpression::Operator::LESS_EQUAL:{
            auto val=popAs<IntValue>()->getValue();
            push(new BoolValue(val<=0));
            break;
        }
        case OperatorFunInvokeExpression::Operator::GREATER:{
            auto val=popAs<IntValue>()->getValue();
            push(new BoolValue(val>0));
            break;
        }
        case OperatorFunInvokeExpression::Operator::GREATER_EQUAL:{
            auto val=popAs<IntValue>()->getValue();
            push(new BoolValue(val>=0));
            break;
        }
        default:
            break;
    }
}

void InterpreterV2::visit(SetOperatorExpression* ex){

    // TODO
    /*
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
        case SetOperatorExpression::Operator::BIT_OR_EQUAL:
        case SetOperatorExpression::Operator::BIT_NOT_EQUAL:{
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
    }*/
}

void InterpreterV2::dup(){
    push(top());
}

void InterpreterV2::over(){
    push(stack[*SP-1]);
}
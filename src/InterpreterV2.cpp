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

void InterpreterV2::initMultiDArray(){

    push(new RefValue(*DI));

    auto dimensionsSize=dynamic_cast<IntValue*>(CX)->getValue();
    
    DX=stack[*BP-dimensionsSize];
    
    auto arraySize=dynamic_cast<IntValue*>(DX)->getValue();
    
    *DI=getAvailableHeapAddress(arraySize);

    if(dimensionsSize>1){
        for(int i=0;i<arraySize;i++){
            CX=new IntValue(dimensionsSize-1);
            initMultiDArray();
            heap[*DI+i+1]=AX;
        }
    }

    AX=new RefValue(*DI);

    *DI=popAs<RefValue>()->getAddress();
}

int InterpreterV2::getAvailableHeapAddress(ClassScope* scope){
    int objSize=scope->getPublicVariables()->size()+scope->getPrivateVariables()->size();
    return getAvailableHeapAddress(objSize);
}

int InterpreterV2::getAvailableHeapAddress(int size){
    int heapAddress=HEAP_SIZE;

    for(int i=0;i<HEAP_SIZE;){
        if(auto reservedObj=heap[i]){
            auto reservedObjSize=dynamic_cast<IntValue*>(reservedObj);
            i+=reservedObjSize->getValue()+1;
            continue;
        }
        int j=i;
        int lastValidCell=i+size;
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

    heap[heapAddress]=new IntValue(size);

    return heapAddress;
}

InterpreterV2::InterpreterV2():
    DI(new int(-1)),
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

void InterpreterV2::visit(NewArrayExpression* ex){

    auto capExs=ex->getCapacities();
    
    for(auto capEx:capExs){
        capEx->accept(this);
        auto cap=topAs<IntValue>()->getValue();
        if(cap<0)
            throw ArrayNegativeCapacityException(cap);
    }

    push(new IntValue(*BP));

    *BP=*SP;

    // dimensions size
    CX=new IntValue(ex->getCapacities().size());

    initMultiDArray();

    *SP=*BP;

    *BP=popAs<IntValue>()->getValue();

    for(auto capEx:capExs){
        pop();
    }

    push(AX);

}

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

    auto op=ex->getOp();

    auto funOfGet=ex->getExOfGet()->getFun().get();
    auto funOfOp=ex->getFunOfOp().get();
    auto funOfSet=ex->getFunOfSet().get();
    
    if(auto isBuiltIn=dynamic_cast<BuiltInFunScope*>(funOfGet)!=nullptr){

        ex->getExHasGetOp()->accept(this);

        ex->getIndexEx()->accept(this);

        CX=pop(); // index

        AX=top(); // ex has get() and set()

        funOfGet->accept(this);

    }else{
        push(new RefValue(*BX));

        ex->getExHasGetOp()->accept(this);
        
        *BX=topAs<RefValue>()->getAddress();

        ex->getIndexEx()->accept(this);

        funOfGet->accept(this);

        CX=pop(); // index

        DX=pop(); // ex has get() and set()

        *BX=popAs<RefValue>()->getAddress();

        push(DX); // ex has get() and set()
    }

    push(CX); // index

    push(AX); // value of get()

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
            // built-in is for a primitive
            if(auto isBuiltIn=dynamic_cast<BuiltInFunScope*>(funOfOp)){
                ex->getValueEx()->accept(this);
                CX=pop(); // 2nd operand i.e. the value of right side
                AX=top(); // 1st operand i.e. value of get()
                funOfOp->accept(this);
            }else{
                push(new RefValue(*BX));
                // AX contains the value of get()
                *BX=dynamic_cast<RefValue*>(AX)->getAddress();
                ex->getValueEx()->accept(this);
                funOfOp->accept(this);
                pop(); // pop value
                *BX=popAs<RefValue>()->getAddress();
            }
            break;
        }
        case SetOperatorExpression::Operator::PRE_INC:
        case SetOperatorExpression::Operator::PRE_DEC:
        case SetOperatorExpression::Operator::POST_INC:
        case SetOperatorExpression::Operator::POST_DEC:{
            // built-in is for a primitive
            if(auto isBuiltIn=dynamic_cast<BuiltInFunScope*>(funOfOp)){
                // AX is the 1st operand and contains the value of get()
                funOfOp->accept(this);
            }else{
                push(new RefValue(*BX));
                // AX contains the value of get()
                *BX=dynamic_cast<RefValue*>(AX)->getAddress();
                funOfOp->accept(this);
                *BX=popAs<RefValue>()->getAddress();
            }
            break;
        }
        default:break;
    }

    // AX has the value of op fun i.e. the value to set

    if(auto isBuiltIn=dynamic_cast<BuiltInFunScope*>(funOfSet)){
        DX=AX;  // AX has the value of op fun i.e. the value to set
        // stack[*SP] is the value of get(), but we don't need it here
        CX=stack[*SP-1]; // index
        AX=stack[*SP-2]; // ex has get() and set() i.e. the array
        funOfSet->accept(this);
        DX=pop();   // the value of get()
        CX=pop();   // index
    }else{
        DX=pop(); // The value of get()
        CX=pop(); // index
        push(DX); // The value of get()
        push(new RefValue(*BX));
        push(CX); // index
        push(AX); // the value to set
        // stack[*SP-4] contains the ex has get() and set()
        *BX=dynamic_cast<RefValue*>(stack[*SP-4])->getAddress();
        funOfSet->accept(this);
        pop();    // the value to set
        CX=pop(); // index
        *BX=popAs<RefValue>()->getAddress();
        DX=pop(); // The value of get()
    }

    // AX has the value of set fun

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
            pop();  // the ex has get() and set()
            push(AX);   // return value of set fun
            break;
        }
        case SetOperatorExpression::Operator::PRE_INC:
        case SetOperatorExpression::Operator::PRE_DEC:{
            AX=pop(); // ex has get() and set()
            if(auto isBuiltIn=dynamic_cast<BuiltInFunScope*>(funOfGet)){
                funOfGet->accept(this);
            }else{
                push(new RefValue(*BX));
                *BX=dynamic_cast<RefValue*>(AX)->getAddress();
                push(CX); // index
                funOfGet->accept(this);
                pop(); // index
                *BX=popAs<RefValue>()->getAddress();
            }
            push(AX);
            break;
        }
        case SetOperatorExpression::Operator::POST_INC:
        case SetOperatorExpression::Operator::POST_DEC:{
            pop();  // the ex has get() and set()
            push(DX); // The value of get()
            break;
        }
        default:break;
    }
}

void InterpreterV2::dup(){
    push(top());
}

void InterpreterV2::over(){
    push(stack[*SP-1]);
}
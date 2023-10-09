#include "BuiltInFunScope.hpp"
#include "ArrayNegativeCapacityException.hpp"
#include "ArrayValue.hpp"
#include "BoolValue.hpp"
#include "ArrayClassScope.hpp"
#include "CharValue.hpp"
#include "FunDecl.hpp"
#include "IValue.hpp"
#include "IntValue.hpp"
#include "Interpreter.hpp"
#include "ObjectValue.hpp"
#include "OperatorFunInvokeExpression.hpp"
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

void InterpreterV2::offsetFunVars(FunScope* scope){
    auto params=scope->getDecl()->params;
    auto locals=scope->getLocals();

    auto paramsOffsets=std::unordered_map<std::wstring,int>{};

    auto offset=-1;
    for(auto paramIt=params->rbegin();paramIt!=params->rend();paramIt++){

        paramsOffsets[
            *paramIt->get()->name
        ]=offset--;

    }

    offset=1;
    for(auto varIt:*scope->getLocals()){
        
        auto paramOffsetIt=paramsOffsets.find(varIt.first);
        
        offsets[varIt.second.get()]=Offset(
            BP,
            (paramOffsetIt==paramsOffsets.end())
            ?offset
            :paramOffsetIt->second
        );

        if(paramOffsetIt==paramsOffsets.end())
            offset++;
    }
}

void InterpreterV2::runStmList(StmListScope* scope){
    for(auto stm:*scope->getStmList()){
        stm->accept(this);
        if(funReturn||loopBreak||loopContinue)
            break;
    }
}

void InterpreterV2::initStmListLocals(StmListScope* scope){
    
    auto locals=scope->getLocals();

    for(auto localIt=locals->begin();localIt!=locals->end();localIt++){
        auto varType=localIt->second->getType();
        
        IValue* val;
        
        if(*varType==*Type::INT)
            val=new IntValue(0);
        
        else if(*varType==*Type::UINT)
            val=new UIntValue(0);
        
        else if(*varType==*Type::LONG)
            val=new LongValue(0);
        
        else if(*varType==*Type::ULONG)
            val=new ULongValue(0);
        
        else if(*varType==*Type::FLOAT)
            val=new FloatValue(0);
        
        else if(*varType==*Type::DOUBLE)
            val=new DoubleValue(0);
        
        else if(*varType==*Type::CHAR)
            val=new CharValue(0);
        
        else if(*varType==*Type::BOOL)
            val=new BoolValue(0);

        // TODO: Ref values

        else if(*varType==*Type::STRING)
            val=new RefValue();

        else if(varType->getClassScope()==Type::ARRAY_CLASS)
            val=new RefValue();

        else
            val=new RefValue();
        
        push(val);
    }
}

void InterpreterV2::invokeNonStaticFun(NonStaticFunInvokeExpression* ex){

    auto insideVal=pop();

    insideVal->linkWithClass();

    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    ex->getFun()->accept(this);

    insideVal->unlinkWithClass();
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

InterpreterV2::InterpreterV2():
    BP(new int(0)),
    SP(new int(0)),
    funReturn(false),
    loopBreak(false),
    loopContinue(false)
{}

InterpreterV2::Assigner::Assigner(InterpreterV2* interpreter)
:interpreter(interpreter){}

void InterpreterV2::Assigner::visit(VarAccessExpression* ex){
    if(!assign){
        ex->accept(interpreter);
    }else{
        auto offset=interpreter->offsets[ex->getVar().get()];
        interpreter->stack[*offset.reg+offset.value]=interpreter->pop();
    }
    assign=!assign;
}

void InterpreterV2::Assigner::visit(NonStaticVarAccessExpression* ex){
    // TODO
    if(!assign){
        /*ex->getInside()->accept(interpreter);
        auto var=interpreter->topAs<ObjectValue>();
        interpreter->push(var->findPropertyValue(ex->getVarName()));*/
    }else{
       /*auto val=interpreter->pop();
        auto var=interpreter->popAs<ObjectValue>();
        var->assignProperty(ex->getVarName(),val);*/
    }
    assign=!assign;
}

void InterpreterV2::Assigner::visit(OperatorFunInvokeExpression* ex){
    interpreter->invokeNonStaticFun(ex);
}

void InterpreterV2::visit(PackageScope* scope){
    for(auto packageIterator:scope->getPackages()){
        packageIterator.second->accept(this);
    }
    for(auto fileIterator:scope->getFiles()){
        fileIterator.second->accept(this);
    }
}

void InterpreterV2::visit(FileScope* scope){

    for(auto funIt:*scope->getPublicFunctions()){
        offsetFunVars(funIt.second.get());
    }
    for(auto funIt:*scope->getPrivateFunctions()){
        offsetFunVars(funIt.second.get());
    }

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

/*void InterpreterV2::visit(ClassScope* scope){

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
        throw; // TODO

    // TODO

    scope->getVarsInitStmList()->accept(this);
}
*/
void InterpreterV2::visit(FunScope* scope){

    push(new IntValue(*BP));

    *BP=*SP;

    auto decl=scope->getDecl();
    auto isConstructor=decl->isConstructor();

    if(isConstructor)
        decl->returnType->getClassScope()->accept(this);

    initStmListLocals(scope);

    for(auto stm:*scope->getStmList()){
        stm->accept(this);
        if(funReturn)
            break;
    }

    if(!funReturn&&!isConstructor)
        push(new UnitValue);
    
    funReturn=false;

    AX=pop();

    *SP=*BP;

    *BP=popAs<IntValue>()->getValue();

    if(!isConstructor)
        return;

    /*auto properties=std::make_shared<std::unordered_map<std::wstring, SharedIValue>>();

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
*/
}

void InterpreterV2::visit(BuiltInFunScope* scope){
    // Built-in functions don't affect BP, so we don't need to push it on the stack

    scope->invokeOnInterpreter(this);

    AX=pop();

}

void InterpreterV2::visit(LoopScope* scope){
    initStmListLocals(scope);
    runStmList(scope);
}

void InterpreterV2::visit(StmListScope* scope){
    initStmListLocals(scope);
    runStmList(scope);
}

void InterpreterV2::visit(VarStm* stm){
    stm->getEx()->accept(this);
    auto offset=offsets[stm->getVar().get()];
    stack[*offset.reg+offset.value]=pop();
}

void InterpreterV2::visit(AssignStatement* stm){
    stm->getLeft()->accept(assigner);
    pop();
    stm->getRight()->accept(this);
    stm->getLeft()->accept(assigner);
}

void InterpreterV2::visit(AugmentedAssignStatement* stm){
    
    stm->getLeft()->accept(assigner);
    auto leftVal=pop();

    stm->getRight()->accept(this);
    auto rightVal=top();

    leftVal->linkWithClass();
    stm->getOpFun()->accept(this);
    leftVal->unlinkWithClass();
    
    stm->getLeft()->accept(assigner);
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
        
    }
    while(true);
}

void InterpreterV2::visit(BreakStatement* stm){
    loopBreak=true;
}

void InterpreterV2::visit(ContinueStatement* stm){
    loopContinue=true;
}

void InterpreterV2::visit(ReturnStatement* stm){
    stm->getEx()->accept(this);
    funReturn=true;
}

void InterpreterV2::visit(ExpressionStatement* stm){
    stm->getEx()->accept(this);
    pop();
}

void InterpreterV2::visit(VarAccessExpression* ex){
    auto offset=offsets[ex->getVar().get()];
    push(stack[*offset.reg+offset.value]);
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

/*void InterpreterV2::visit(NewObjectExpression* ex){

    // TODO

    push(new IntValue(bp));

    bp=sp;

    auto args=ex->getArgs();

    for(auto arg:*args){
        arg->accept(this);
    }

    ex->getConstructor()->accept(this);

    sp=bp;

    bp=popAs<IntValue>()->getValue();

    push(ax); // return value
}*/

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

//void InterpreterV2::visit(NonStaticVarAccessExpression* ex){
    // TODO
    /*ex->getInside()->accept(this);
    auto propVal=popAs<ObjectValue>()->findPropertyValue(ex->getVarName());
    push(propVal);*/
//}

//void InterpreterV2::visit(NonStaticFunInvokeExpression* ex){
    // TODO
    /*ex->getInside()->accept(this);
    invokeNonStaticFun(ex);*/
//}

void InterpreterV2::visit(OperatorFunInvokeExpression* ex){
    // TODO
    /*
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
    }*/
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

InterpreterV2::Offset::Offset(int* reg, int value):
    reg(reg),
    value(value)
{}

InterpreterV2::Offset::Offset():
    reg(0),
    value(0)
{}
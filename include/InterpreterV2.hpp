#pragma once
#include "ASTVisitor.hpp"

#include "IValue.hpp"
#include "PackageScope.hpp"
#include "FileScope.hpp"
#include "ClassScope.hpp"
#include "FunScope.hpp"
#include "LoopScope.hpp"
#include "SharedPtrTypes.hpp"
#include "StmListScope.hpp"
#include "VarStm.hpp"
#include "IfStatement.hpp"
#include "AssignStatement.hpp"
#include "AugmentedAssignStatement.hpp"
#include "Variable.hpp"
#include "VarsOffsetSetter.hpp"
#include "WhileStatement.hpp"
#include "DoWhileStatement.hpp"
#include "BreakStatement.hpp"
#include "ContinueStatement.hpp"
#include "ReturnStatement.hpp"
#include "ExpressionStatement.hpp"
#include "VarAccessExpression.hpp"
#include "FunInvokeExpression.hpp"
#include "NewObjectExpression.hpp"
#include "NewArrayExpression.hpp"
#include "LiteralExpression.hpp"
#include "UnitExpression.hpp"
#include "LogicalExpression.hpp"
#include "NonStaticVarAccessExpression.hpp"
#include "NonStaticFunInvokeExpression.hpp"
#include "OperatorFunInvokeExpression.hpp"
#include "SetOperatorExpression.hpp"

#include "ArrayValue.hpp"
#include "RefValue.hpp"
#include <memory>
#include <stack>
#include <unordered_map>

#define STACK_SIZE 64
#define HEAP_SIZE  64

class BuiltInFunScope;

class InterpreterV2:public ASTVisitor{
    public:
        class Assigner:public ASTVisitor{
            private:
                InterpreterV2* interpreter;
                bool assign=false;
            public:
                Assigner(InterpreterV2* interpreter);
                void visit(VarAccessExpression* ex)override;
                void visit(NonStaticVarAccessExpression* ex)override;
                void visit(OperatorFunInvokeExpression* ex)override;
        };
        Assigner* assigner;
    private:
        bool funReturn;
        bool loopBreak;
        bool loopContinue;
        IValue* stack[STACK_SIZE];
        IValue* heap[HEAP_SIZE];
        IValue* AX;

        void runStmList(StmListScope* scope);
        void initStmListLocals(StmListScope* scope);
        
        void invokeNonStaticFun(NonStaticFunInvokeExpression* ex);
        /**
        NOTE: The @param type should be of type Type::Array. Be careful as we want to avoid casting.
        */
        ArrayValue* initMultiDArray(
            int capIndex,
            int capacitiesSize,
            int capacities[],
            SharedType type
        );
    public:
        InterpreterV2();
        void visit(PackageScope* scope)override;
        void visit(FileScope* scope)override;
        //void visit(ClassScope* scope)override;
        void visit(FunScope* scope)override;                    // ANCHOR: DONE
        void visit(BuiltInFunScope* scope)override;             // ANCHOR: DONE
        void visit(LoopScope* scope)override;
        void visit(StmListScope* scope)override;
        void visit(VarStm* stm)override;                        // ANCHOR: DONE
        void visit(AssignStatement* stm)override;
        void visit(AugmentedAssignStatement* stm)override;
        void visit(IfStatement* stm)override;
        void visit(WhileStatement* stm)override;
        void visit(DoWhileStatement* stm)override;
        void visit(BreakStatement* stm)override;                // ANCHOR: DONE
        void visit(ContinueStatement* stm)override;             // ANCHOR: DONE
        void visit(ReturnStatement* stm)override;               // ANCHOR: DONE
        void visit(ExpressionStatement* stm)override;           // ANCHOR: DONE
        void visit(VarAccessExpression* ex)override;            // ANCHOR: DONE
        void visit(FunInvokeExpression* ex)override;            // ANCHOR: DONE
        //void visit(NewObjectExpression* ex)override;            // TODO
        //void visit(NewArrayExpression* ex)override;             // TODO
        void visit(LiteralExpression* ex)override;              // ANCHOR: DONE
        void visit(UnitExpression* ex)override;                 // ANCHOR: DONE
        void visit(LogicalExpression* ex)override;              // ANCHOR: DONE
        //void visit(NonStaticVarAccessExpression* ex)override;   // TODO
        //void visit(NonStaticFunInvokeExpression* ex)override;   // TODO
        void visit(OperatorFunInvokeExpression* ex)override;    // TODO
        void visit(SetOperatorExpression* ex)override;          // TODO


        void dup();
        void over();
        void push(IValue* val);
        IValue* top();
        IValue* pop();
        template<typename T>
        T* popAs();
        template<typename T>
        T* topAs();

        std::unordered_map<Variable*, VarsOffsetSetter::Offset> offsets;
        int*const BX;
        int*const BP;
        int*const SP;
};

template<typename T>
inline T* InterpreterV2::popAs(){
    return dynamic_cast<T*>(pop());
}

template<typename T>
inline T* InterpreterV2::topAs(){
    return dynamic_cast<T*>(top());
}

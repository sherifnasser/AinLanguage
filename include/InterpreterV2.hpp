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
        class LeftSideAssigner:public ASTVisitor{
            private:
                InterpreterV2* interpreter;
            public:
                LeftSideAssigner(InterpreterV2* interpreter);
                void visit(VarAccessExpression* ex)override;
                void visit(NonStaticVarAccessExpression* ex)override;
        };
        class RightSideAssigner:public ASTVisitor{
            private:
                InterpreterV2* interpreter;
            public:
                RightSideAssigner(InterpreterV2* interpreter);
                void visit(VarAccessExpression* ex)override;
                void visit(NonStaticVarAccessExpression* ex)override;
        };

        LeftSideAssigner* lAssigner;
        RightSideAssigner* rAssigner;
    private:
        bool funReturn;
        bool loopBreak;
        bool loopContinue;
        IValue* stack[STACK_SIZE];

        void runStmList(StmListScope* scope);
        void offsetStmListLocals(int size);
        
        void invokeNonStaticFun(NonStaticFunInvokeExpression* ex);
        void invokeNonStaticBuiltInFun(NonStaticFunInvokeExpression* ex);
        void invokeBuiltInOpFun(OperatorFunInvokeExpression* ex);
        void initMultiDArray();
        int getAvailableHeapAddress(ClassScope* scope);
        int getAvailableHeapAddress(int size);
    public:
        InterpreterV2();
        void visit(PackageScope* scope)override;
        void visit(FileScope* scope)override;
        void visit(ClassScope* scope)override;                  // ANCHOR: DONE
        void visit(FunScope* scope)override;                    // ANCHOR: DONE
        void visit(BuiltInFunScope* scope)override;             // ANCHOR: DONE
        void visit(LoopScope* scope)override;                   // ANCHOR: DONE
        void visit(StmListScope* scope)override;                // ANCHOR: DONE
        void visit(VarStm* stm)override;                        // ANCHOR: DONE
        void visit(AssignStatement* stm)override;               // ANCHOR: DONE
        void visit(AugmentedAssignStatement* stm)override;      // ANCHOR: DONE
        void visit(IfStatement* stm)override;                   // ANCHOR: DONE
        void visit(WhileStatement* stm)override;                // ANCHOR: DONE
        void visit(DoWhileStatement* stm)override;              // ANCHOR: DONE
        void visit(BreakStatement* stm)override;                // ANCHOR: DONE
        void visit(ContinueStatement* stm)override;             // ANCHOR: DONE
        void visit(ReturnStatement* stm)override;               // ANCHOR: DONE
        void visit(ExpressionStatement* stm)override;           // ANCHOR: DONE
        void visit(VarAccessExpression* ex)override;            // ANCHOR: DONE
        void visit(FunInvokeExpression* ex)override;            // ANCHOR: DONE
        void visit(NewObjectExpression* ex)override;            // ANCHOR: DONE
        void visit(NewArrayExpression* ex)override;             // ANCHOR: DONE
        void visit(LiteralExpression* ex)override;              // ANCHOR: DONE
        void visit(UnitExpression* ex)override;                 // ANCHOR: DONE
        void visit(LogicalExpression* ex)override;              // ANCHOR: DONE
        void visit(NonStaticVarAccessExpression* ex)override;   // ANCHOR: DONE
        void visit(NonStaticFunInvokeExpression* ex)override;   // ANCHOR: DONE
        void visit(OperatorFunInvokeExpression* ex)override;    // ANCHOR: DONE
        void visit(SetOperatorExpression* ex)override;          // ANCHOR: DONE


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
        IValue* AX;
        IValue* CX;
        IValue* DX;
        int*const DI;
        int*const BX;
        int*const BP;
        int*const SP;

        IValue* heap[HEAP_SIZE];
};

template<typename T>
inline T* InterpreterV2::popAs(){
    return dynamic_cast<T*>(pop());
}

template<typename T>
inline T* InterpreterV2::topAs(){
    return dynamic_cast<T*>(top());
}
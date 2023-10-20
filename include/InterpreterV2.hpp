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
#include <unordered_map>

#define DATA_SIZE  64
#define HEAP_SIZE  64
#define STACK_SIZE 64
#define MEM_SIZE   DATA_SIZE+HEAP_SIZE+STACK_SIZE

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

        void runStmList(StmListScope* scope);
        void reserveSpaceForStmListLocals(int size);
        void removeReservedSpaceForStmListLocals(int size);
        
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
        void push(SharedIValue val);
        SharedIValue top();
        SharedIValue pop();
        template<typename T>
        std::shared_ptr<T> popAs();
        template<typename T>
        std::shared_ptr<T> topAs();

        std::unordered_map<Variable*, VarsOffsetSetter::Offset> offsets;
        SharedIValue AX;
        SharedIValue CX;
        SharedIValue DX;
        int*const DI;
        int*const BX;
        int*const BP;
        int*const SP;
        const int*const DS;
        const int*const SS;
        SharedIValue memory[MEM_SIZE];
};

template<typename T>
inline std::shared_ptr<T> InterpreterV2::popAs(){
    return std::dynamic_pointer_cast<T>(pop());
}

template<typename T>
inline std::shared_ptr<T> InterpreterV2::topAs(){
    return std::dynamic_pointer_cast<T>(top());
}
#pragma once
#include "ASTVisitor.hpp"

#include "BuiltInFunScope.hpp"
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
#include <memory>
#include <stack>

class Interpreter:public ASTVisitor{
    public:
        class Assigner:public ASTVisitor{
            private:
                Interpreter* interpreter;
                bool assign=false;
            public:
                Assigner(Interpreter* interpreter);
                void visit(VarAccessExpression* ex)override;
                void visit(NonStaticVarAccessExpression* ex)override;
                void visit(OperatorFunInvokeExpression* ex)override;
        };
        Assigner* assigner;
    private:
        bool funReturn;
        bool loopBreak;
        bool loopContinue;
        std::stack<SharedIValue> valuesStack;
        void push(SharedIValue val);
        SharedIValue top();
        SharedIValue pop();
        void runStmList(StmListScope* scope);
        template<typename T>
        std::shared_ptr<T> popAs();
        template<typename T>
        std::shared_ptr<T> topAs();
        void invokeNonStaticFun(NonStaticFunInvokeExpression* ex);
        /**
        NOTE: The @param type should be of type Type::Array. Be careful as we want to avoid casting.
        */
        std::shared_ptr<ArrayValue> initMultiDArray(
            int capIndex,
            int capacitiesSize,
            int capacities[],
            SharedType type
        );
    public:
        Interpreter();
        Interpreter(Assigner* assigner);
        void visit(PackageScope* scope)override;
        void visit(FileScope* scope)override;
        void visit(ClassScope* scope)override;
        void visit(FunScope* scope)override;
        void visit(BuiltInFunScope* scope)override;
        void visit(LoopScope* scope)override;
        void visit(StmListScope* scope)override;
        void visit(VarStm* stm)override;
        void visit(AssignStatement* stm)override;
        void visit(AugmentedAssignStatement* stm)override;
        void visit(IfStatement* stm)override;
        void visit(WhileStatement* stm)override;
        void visit(DoWhileStatement* stm)override;
        void visit(BreakStatement* stm)override;
        void visit(ContinueStatement* stm)override;
        void visit(ReturnStatement* stm)override;
        void visit(ExpressionStatement* stm)override;
        void visit(VarAccessExpression* ex)override;
        void visit(FunInvokeExpression* ex)override;
        void visit(NewObjectExpression* ex)override;
        void visit(NewArrayExpression* ex)override;
        void visit(LiteralExpression* ex)override;
        void visit(UnitExpression* ex)override;
        void visit(LogicalExpression* ex)override;
        void visit(NonStaticVarAccessExpression* ex)override;
        void visit(NonStaticFunInvokeExpression* ex)override;
        void visit(OperatorFunInvokeExpression* ex)override;
        void visit(SetOperatorExpression* ex)override;
};

template<typename T>
inline std::shared_ptr<T> Interpreter::popAs(){
    return std::dynamic_pointer_cast<T>(pop());
}

template<typename T>
inline std::shared_ptr<T> Interpreter::topAs(){
    return std::dynamic_pointer_cast<T>(top());
}

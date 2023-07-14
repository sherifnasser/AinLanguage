#pragma once
#include "IExpression.hpp"
#include "IStatement.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>

class AssignStatement:public IStatement{
    public:
        class AssignExpression:public IExpression{
            protected:
                AssignExpression
                (int lineNumber,SharedType returnType)
                :IExpression(lineNumber, returnType){}
            public:
                virtual void assign(SharedIValue newVal)=0;
                virtual ~AssignExpression(){}
        };

        AssignStatement(
            int lineNumber,
            SharedStmListScope runScope,
            std::shared_ptr<AssignExpression> ex,
            SharedIExpression newValEx
        );
        void check() override;
        void run() override;
    
    private:
        std::shared_ptr<AssignExpression> ex;
        SharedIExpression newValEx;
};
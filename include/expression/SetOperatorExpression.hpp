#pragma once
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"
class SetOperatorExpression:public IExpression{
    public:
        enum class Operator{
            PLUS_EQUAL,MINUS_EQUAL,
            TIMES_EQUAL,DIV_EQUAL,
            MOD_EQUAL,POW_EQUAL,

            SHR_EQUAL,SHL_EQUAL,
            BIT_AND_EQUAL,XOR_EQUAL,
            BIT_OR_EQUAL,BIT_NOT_EQUAL,
            
            EQUAL,

            PRE_INC,PRE_DEC,
            POST_INC,POST_DEC,

        };

        SetOperatorExpression(
            Operator op,
            SharedOpFunInvokeExpression exOfGet,
            SharedIExpression valueEx
        );

        void accept(ASTVisitor *visitor) override;

        SharedOpFunInvokeExpression getExOfGet()const;

        SharedIExpression getValueEx()const;

        SharedFunScope getFun()const;

        void setFun(SharedFunScope fun);
        

    private:
        SharedOpFunInvokeExpression exOfGet;
        SharedIExpression valueEx;
        SharedFunScope fun;
        Operator op;
};
#pragma once
#include "ASTNode.hpp"
#include "SharedPtrTypes.hpp"
#include <memory>
#include <string>
class IExpression:public ASTNode{
    protected:
        int lineNumber;
        SharedType returnType;
    public:
        IExpression(int lineNumber,SharedType returnType);
        virtual SharedIValue evaluate()=0;
        SharedType getReturnType();
        void setReturnType(SharedType returnType);
        virtual ~IExpression();

        template<typename T>
        std::shared_ptr<T> evaluateAs();

        int getLineNumber()const;

        static bool isAssignableExpression(SharedIExpression ex);

};

template<typename T>
inline std::shared_ptr<T> IExpression::evaluateAs(){
    auto eval=evaluate();
    return std::dynamic_pointer_cast<T>(eval);
}
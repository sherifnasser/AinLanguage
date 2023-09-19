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
        virtual void check(SharedBaseScope checkScope)=0;
        SharedType getReturnType();
        virtual ~IExpression();

        template<typename T>
        std::shared_ptr<T> evaluateAs();

        int getLineNumber() const;
};

template<typename T>
inline std::shared_ptr<T> IExpression::evaluateAs(){
    auto eval=evaluate();
    return std::dynamic_pointer_cast<T>(eval);
}

inline int IExpression::getLineNumber() const { return lineNumber; }
#pragma once
#include "SharedPtrTypes.hpp"
#include <memory>
#include <string>
class IExpression{
    protected:
        int lineNumber;
        SharedType returnType;
    public:
        IExpression(int lineNumber,SharedType returnType);
        virtual std::vector<std::wstring> prettyPrint()=0;
        virtual SharedIValue evaluate()=0;
        virtual void check(SharedBaseScope checkScope)=0;
        SharedType getReturnType();
        virtual ~IExpression();

        template<typename T>
        std::shared_ptr<T> evaluateAs();
};

template<typename T>
inline std::shared_ptr<T> IExpression::evaluateAs(){
    auto eval=evaluate();
    return std::dynamic_pointer_cast<T>(eval);
}

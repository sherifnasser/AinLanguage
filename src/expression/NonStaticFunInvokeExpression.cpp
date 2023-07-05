#include "NonStaticFunInvokeExpression.hpp"

NonStaticFunInvokeExpression::NonStaticFunInvokeExpression(
    int lineNumber,
    std::wstring funName,
    SharedVector<SharedIExpression> args,
    SharedIExpression inside
)
    : IExpression(lineNumber,nullptr),
      funName(funName),
      args(args),
      inside(inside){}

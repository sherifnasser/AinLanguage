#include "FunInvokeExpression.hpp"

FunInvokeExpression::FunInvokeExpression(int lineNumber,std::wstring funName, SharedVector<SharedIExpression> args)
    : IExpression(lineNumber,nullptr),
      funName(funName),
      args(args){}



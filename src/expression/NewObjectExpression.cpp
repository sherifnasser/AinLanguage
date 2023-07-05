#include "NewObjectExpression.hpp"
#include "IExpression.hpp"
#include "SharedPtrTypes.hpp"

NewObjectExpression::NewObjectExpression(
    int lineNumber,
    SharedType type,
    SharedVector<SharedIExpression> args
):IExpression(lineNumber,type),args(args){}
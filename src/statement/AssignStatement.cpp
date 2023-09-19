#include "AssignStatement.hpp"
#include "SharedPtrTypes.hpp"
#include "StmListScope.hpp"
#include "Type.hpp"
#include "semantics/UnexpectedTypeException.hpp"

AssignStatement::AssignStatement(
    int lineNumber,
    SharedStmListScope runScope,
    SharedIExpression ex,
    SharedIExpression newValEx
)
:IStatement(lineNumber,runScope),ex(ex),newValEx(newValEx){}

SharedIExpression AssignStatement::getEx()const{
    return ex;
}

SharedIExpression AssignStatement::getNewValEx()const{
    return newValEx;
}

#include "VarStm.hpp"
#include "IExpression.hpp"
#include "Variable.hpp"
#include "Type.hpp"
#include "statement/TypeMismatchException.hpp"

VarStm::VarStm(
    int lineNumber,
    SharedBaseScope runScope,
    SharedVariable var,
    SharedIExpression ex
)
    : IStatement(lineNumber,runScope),
      var(var),
      ex(ex){}

SharedVariable VarStm::getVar()const{
    return var;
}

void VarStm::run(){
    auto val=ex->evaluate();
    var->setValue(val);
}

SharedIExpression VarStm::getEx()const{
    return ex;
}

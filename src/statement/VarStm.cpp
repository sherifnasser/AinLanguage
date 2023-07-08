#include "VarStm.hpp"

VarStm::VarStm(
    int lineNumber,
    SharedBaseScope runScope,
    SharedVariable var,
    SharedIExpression ex
)
    : IStatement(lineNumber,runScope),
      var(var),
      ex(ex){}

SharedVariable VarStm::getVar() const { return var; }

void VarStm::check() {
    
}

void VarStm::run() {
    
}

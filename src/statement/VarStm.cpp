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

SharedVariable VarStm::getVar() const { return var; }

void VarStm::check(){
    ex->check(runScope);

    auto exType=ex->getReturnType();

    if(var->hasImplicitType()){
        var->setType(exType);
        return;
    }

    if(*var->getType()==*exType)
        return;
    
    // TODO: message
    throw TypeMismatchException(
        L"متغير "+*var->getName()+L": "+*var->getType()->getName(),
        L"تعبير: "+*ex->getReturnType()->getName());

}

void VarStm::run() {
    auto val=ex->evaluate();
    var->setValue(val);
}

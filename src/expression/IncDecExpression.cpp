#include "IncDecExpression.hpp"
#include "FunScope.hpp"
#include "OperatorFunInvokeExpression.hpp"
#include "OperatorFunctions.hpp"
#include "SharedPtrTypes.hpp"
#include "IValue.hpp"
#include "Type.hpp"
#include "UnexpectedTypeException.hpp"
#include <map>
#include <memory>
#include <utility>

IncDecExpression::IncDecExpression(
    int lineNumber,
    std::wstring opName,
    std::shared_ptr<AssignStatement::AssignExpression> ex
)
    : OperatorFunInvokeExpression(
        lineNumber,
        opName,
        std::make_shared<std::vector<SharedIExpression>>(
            std::vector<SharedIExpression>{}
        ),
        ex
    ),ex(ex)
{}

std::pair<SharedIValue, SharedIValue> IncDecExpression::evaluateNewAndOldValues() {
    
    auto oldVal=ex->evaluate();

    oldVal->linkWithClass();

    auto newVal=this->fun->invoke(
        std::make_shared<std::map<std::wstring, SharedIValue>>()
    );

    oldVal->unlinkWithClass();
    
    ex->assign(newVal);

    return std::pair{newVal,oldVal};
}

void IncDecExpression::check(SharedBaseScope checkScope){
    OperatorFunInvokeExpression::check(checkScope);

    auto t1=this->ex->getReturnType();
    auto t2=this->fun->getReturnType();
    if(t1->getClassScope()!=t2->getClassScope())
        throw UnexpectedTypeException(
            lineNumber,
            *t1->getName(),
            *t2->getName()
        );
}

std::vector<std::wstring> IncDecExpression::PreIncDecExpression::prettyPrint(){
    auto superPrints=OperatorFunInvokeExpression::prettyPrint();

    auto lineNumStr=std::to_wstring(lineNumber);

    superPrints[0]=L"\033[36;1mPreOperatorExpression \'"+funName+L"\' at "+lineNumStr+L"\033[0m";

    return superPrints;
}

SharedIValue IncDecExpression::PreIncDecExpression::evaluate(){
    return evaluateNewAndOldValues().first; // newVal
}

std::vector<std::wstring> IncDecExpression::PostIncDecExpression::prettyPrint(){
    auto superPrints=OperatorFunInvokeExpression::prettyPrint();

    auto lineNumStr=std::to_wstring(lineNumber);

    superPrints[0]=L"\033[36;1mPostOperatorExpression \'"+funName+L"\' at "+lineNumStr+L"\033[0m";

    return superPrints;
}

SharedIValue IncDecExpression::PostIncDecExpression::evaluate(){
    return evaluateNewAndOldValues().second; // oldVal
}

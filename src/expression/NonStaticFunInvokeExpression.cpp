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

std::vector<std::wstring> NonStaticFunInvokeExpression::prettyPrint(){
    auto prints=std::vector<std::wstring>();
    auto lineNumStr=std::to_wstring(lineNumber);
    prints.push_back(L"NonStaticFunInvokeExpression \'"+funName+L"\' at "+lineNumStr);

    auto insidePrints=inside->prettyPrint();
    
    insidePrints[0]=
    ((args->size()==0)?L"└──":L"├──")+
    (L"\033[1;33m"+insidePrints[0]+L"\033[0m");

    for(int i=1;i<insidePrints.size();i++){   
        insidePrints[i]=
            ((args->size()==0)?L"    ":L"│   ")+insidePrints[i];
    }

    prints.insert(prints.end(),insidePrints.begin(),insidePrints.end());

    for(int i=0;i<args->size();i++){
        auto argPrints=args->at(i)->prettyPrint();
        
        argPrints[0]=
            ((i==args->size()-1)?L"└──":L"├──")+argPrints[0];

        for(int j=1;j<argPrints.size();j++){
            argPrints[j]=
                ((i==args->size()-1)?L"    ":L"│   ")+argPrints[j];
        }

        prints.insert(prints.end(),argPrints.begin(),argPrints.end());
    }

    return prints;
}

SharedIValue NonStaticFunInvokeExpression::evaluate() {
    
}

void NonStaticFunInvokeExpression::check(SharedBaseScope checkScope) {
    
}

NonStaticFunInvokeExpression::~NonStaticFunInvokeExpression(){}
